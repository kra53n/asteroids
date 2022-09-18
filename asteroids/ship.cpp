#include <SDL.h>
#include <math.h>
#include <stdio.h>

#include "ship.h"
#include "music.h"
#include "score.h"
#include "funcs.h"
#include "bullet.h"
#include "vector.h"
#include "window.h"
#include "health.h"
#include "config.h"
#include "texture.h"
#include "animation.h"

void EngineUpdate(Animation& self)
{
    int ticks = SDL_GetTicks();
    if (!(ticks - self.ticks >= ENGINE_DELAY)) return;

    self.frame = self.frame < ENGINE_FRAMES - 1 ? ++self.frame : 0;
}

void EngineDraw(Animation& self, Ship& ship, bool cond)
{
    if (!cond) return;

    Vec pos;
    VecSetLen(pos, (ship.tex.dstrect.w + self.textures->dstrect.w) / 2);
    VecSetAngle(pos, -ship.tex.angle);

    SDL_Rect dstrect = self.textures->dstrect;
    dstrect.x = ship.tex.dstrect.x + (ship.tex.dstrect.w - self.textures->dstrect.w) / 2 - pos.x;
    dstrect.y = ship.tex.dstrect.y + (ship.tex.dstrect.h - self.textures->dstrect.h) / 2 - pos.y;

    SDL_RenderCopyEx(ren, self.textures[self.frame].tex, 0, &dstrect, ship.tex.angle, 0, SDL_FLIP_NONE);
}

void ShipInit(Ship& self, const char* filename, int instance)
{
    self.ticks = SDL_GetTicks();
    self.instance = instance;
    self.bulletType = 0;
    self.active = true;

    switch (self.instance)
    {
    case SHIP1: self.acts = SHIP1_ACTIONS; break;
    case SHIP2: self.acts = SHIP2_ACTIONS; break;
    }

    self.tex = loadTexture(filename);
    self.tex.dstrect.w *= SHIP_SCALE_COEFF;
    self.tex.dstrect.h *= SHIP_SCALE_COEFF;

    self.tex.dstrect.x = (winWdt - self.tex.dstrect.w) / 2;
    self.tex.dstrect.y = (winHgt - self.tex.dstrect.h) / 2;

    self.rad = (int)getRadius(self.tex.dstrect) - SHIP_RADIUS_NARROWING;

    AnimationInit(self.engine, ENGINE_FRAMES, ENGINE_FILENAME, ENGINE_FILENAME_TYPE, SHIP_SCALE_COEFF);
    ScoreInit(self.score, { 10, 3 }, 0, "Score: ");
    HealthInit(self.health, { 10, 50, 250, 25 }, 100);
    BulletsInit(self.bullets);
}

void ShipReset(Ship& self, SDL_Point pos)
{
    BulletsDestroy(self.bullets);
    BulletsInit(self.bullets);

    self.score.point = 0;
    ScoreUpdate(self.score);

    self.health.point = 100;

    float center = getRadius(self.tex.dstrect);
    self.tex.dstrect.x = pos.x - center;
    self.tex.dstrect.y = pos.y - center;
    self.tex.angle = 0;

    self.vel = { 0, 0 };
    self.acc = { 0, 0 };
    self.angularVel = 0;
}

void ShipUpdateActions(Ship& self, Keys& keys, int gameState)
{
    switch (gameState)
    {
    case GAME_STATE_SOLO:
        self.acts.up    = keys.up    || keys.w;
        self.acts.down  = keys.down  || keys.s;
        self.acts.left  = keys.left  || keys.a;
        self.acts.right = keys.right || keys.d;
        self.acts.shoot = keys.rctrl || keys.space;
        break;

    case GAME_STATE_SEAT:
        switch (self.instance)
        {
        case SHIP1:
            self.acts.up    = keys.w;
            self.acts.down  = keys.s;
            self.acts.left  = keys.a;
            self.acts.right = keys.d;
            self.acts.shoot = keys.space;
            break;

        case SHIP2:
            self.acts.up    = keys.up;
            self.acts.down  = keys.down;
            self.acts.left  = keys.left;
            self.acts.right = keys.right;
            self.acts.shoot = keys.rctrl;
            break;
        }
        break;
    }
}

void ShipUpdateVelocity(Ship& self)
{
    if (fabs(self.vel.x) > SHIP_MAX_VEL)
        updateMaxValue(self.vel.x, SHIP_MAX_VEL);
    if (fabs(self.vel.y) > SHIP_MAX_VEL)
        updateMaxValue(self.vel.y, SHIP_MAX_VEL);

    self.tex.dstrect.x += self.vel.x;
    self.tex.dstrect.y -= self.vel.y;

    updateMaxValue(self.angularVel, SHIP_MAX_ANGULAR_VEL);
    self.tex.angle += self.angularVel;
}

void ShipUpdatAcceleration(Ship& self)
{
    if (self.acts.up)
    {
        self.acc = { 0.6, 0 };
        VecSetAngle(self.acc, self.tex.angle);
        VecSumCoords(self.vel, self.acc);
    }

    if (self.acts.left)
        self.angularVel -= SHIP_ANGULAR_ACC;
    if (self.acts.right)
        self.angularVel += SHIP_ANGULAR_ACC;
    self.angularVel /= SHIP_INCREASE_ANGULAR_ACC;
}

void ShipUpdateTicks(Ship& self)
{
    int ticks = SDL_GetTicks();
    if (ticks - self.ticks < 1000) return;
    self.ticks = ticks;

    if (self.acts.up) return;
    self.vel.x /= 1.8;
    self.vel.y /= 1.8;
}

void ShipUpdateCollisionWithAstroids(Ship& self, Asteroids& asters)
{
    SDL_Point shipPoint = {
        self.tex.dstrect.x + self.tex.dstrect.w/2 ,
        self.tex.dstrect.y + self.tex.dstrect.h/2 
    };

    for (Asteroid* aster = asters.head; aster != NULL; aster = aster->next)
    {
        int asterR = asters.texture[aster->type].dstrect.h / 2;
        SDL_Point asterPoint = {
            aster->pos.x + asterR,
            aster->pos.y + asterR
        };

        if (!isCircsColliding(shipPoint, self.rad, asterPoint, asterR)) continue;
        
        VecSetAngleByCoords(self.vel, asterPoint, shipPoint);
        VecSetAngleByCoords(aster->vel, shipPoint, asterPoint);

        float asterRebound = 60 / ASTEROIDS[aster->type].mass;
        float shipRebound = 70 / asterRebound;
        asterRebound /= self.rad / 10;
        asterRebound *= self.rad / 10;

        VecSetLen(self.vel, 70 / asterRebound);
        VecSetLen(aster->vel, asterRebound);
        
        HealthUpdate(self.health, ASTEROIDS[aster->type].damage);
        aster->health -= 10;

        MusicEffectsPlay(MUSIC_COLLIDED);
    }
}

void ShipShoot(Ship& self, int type)
{
    int ticks = SDL_GetTicks();
    if (ticks - self.bullets.ticks < BULLETS[type].delay) return;
    self.bullets.ticks = ticks;
    
    Bullet* bullet = 0;

    switch (type)
    {
    case 0:
        bullet = BulletsPush(self.bullets, self.tex, type);
        break;

    case 1:
        for (int i = -90; i <= 90; i += 180)
        {
            bullet = BulletsPush(self.bullets, self.tex, type);

            Vec pos;
            VecSetLen(pos, getRadius(self.tex.dstrect));
            VecSetAngle(pos, -self.tex.angle + i);
            VecSetAngle(bullet->vel, self.tex.angle);

            SDL_Point center = getRectCenter(self.tex.dstrect);
            bullet->pos.x = center.x + pos.x;
            bullet->pos.y = center.y + pos.y;
        }
        break;

    case 2:
        for (int angle = -45; angle < 45; angle += 15)
        {
            bullet = BulletsPush(self.bullets, self.tex, type);
            VecSetAngle(bullet->vel, VecGetAngle(bullet->vel) - angle);
        }
        break;

    case 3:
        for (int angle = -180; angle < 180; angle += 30)
        {
            bullet = BulletsPush(self.bullets, self.tex, type);

            Vec pos;
            VecSetLen(pos, self.tex.dstrect.w);
            VecSetAngle(pos, VecGetAngle(bullet->vel) - angle);

            bullet->pos = getRectCenter(self.tex.dstrect);
            bullet->pos.x += pos.x;
            bullet->pos.y += pos.y;

            VecSetAngle(bullet->vel, VecGetAngle(bullet->vel) + angle);
        }
        break;
    }

    if (bullet)
        MusicEffectsPlay(BULLETS[bullet->type].chunk);
}

bool ShipUpdateBulletCollisionWithEnemy(Ship& self, SDL_Rect& enemyRect,
    Health& enemyHealth, bool& enemyInited, Bullet* bullet
)
{
    if (!isPointInCirc(
        getRectCenter(enemyRect),
        getRadius(enemyRect),
        { bullet->pos.x, bullet->pos.y }
    )) return false;

    HealthUpdate(enemyHealth, BULLETS[bullet->type].damage);
    if (enemyHealth.point <= 0)
    {
        ScoreUpdate(self.score, ENEMY_HEALTH);
        enemyInited = false;
    }
    BulletsDelBullet(self.bullets, bullet);

    return true;
}

bool ShipUpdateBulletCollisionWithShip(Ship& self, Ship& ship, Bullet* bullet)
{
    if (!(self.active && ship.active)) return false;

    if (!isPointInCirc(
        getRectCenter(ship.tex.dstrect),
        ship.rad,
        { bullet->pos.x, bullet->pos.y }
    )) return false;
    
    ship.health.point -= BULLETS[bullet->type].damage;
    HealthUpdate(ship.health, BULLETS[bullet->type].damage);
    BulletsDelBullet(self.bullets, bullet);

    return true;
}

void ShipUpdateBullets(Ship& self, Ship& ship, Asteroids& asters,
    SDL_Rect& enemyRect, bool& enemyActive, Health& enemyHealth
)
{
    for (Bullet* cur = self.bullets.head; cur != NULL;)
    {
        Bullet* curNext = cur->next;

        cur->pos.x += cur->vel.x;
        cur->pos.y -= cur->vel.y;

        if (
            BulletsUpdateCollisionWithAstroids(self.bullets, cur, asters, self.score) ||
            ShipUpdateBulletCollisionWithEnemy(self, enemyRect, enemyHealth, enemyActive, cur) ||
            ShipUpdateBulletCollisionWithShip(self, ship, cur)
        )
        {
            cur = curNext;
            continue;
        }

        if (
            cur->pos.x < 0 || cur->pos.x > winWdt || 
            cur->pos.y < 0 || cur->pos.y > winHgt
        )
        {
            BulletsDelBullet(self.bullets, cur);
        }

        cur = curNext;
    }

    if (!self.acts.shoot) return;
    ShipShoot(self, self.bulletType);
}

void ShipUpdateCollisionWithShip(Ship& self, Ship& ship)
{
    if (!(self.active && ship.active)) return;

    SDL_Point s1Center = getRectCenter(self.tex.dstrect);
    SDL_Point s2Center = getRectCenter(ship.tex.dstrect);

    if (!isCircsColliding(s1Center, self.rad, s2Center, ship.rad)) return;
    
    HealthUpdate(self.health, SHIP_DAMAGE);
    HealthUpdate(ship.health, SHIP_DAMAGE);

    VecSetAngleByCoords(self.vel, s2Center, s1Center);
    VecSetAngleByCoords(ship.vel, s1Center, s2Center);
    
    float maxVel = max(VecGetLen(self.vel), VecGetLen(ship.vel));
    VecSetLen(self.vel, maxVel);
    VecSetLen(ship.vel, maxVel);

    MusicEffectsPlay(MUSIC_COLLIDED);
}

void ShipUpdate(Ship& self, Ship& ship, Asteroids& asters, SDL_Rect& enemyRect,
    Health& enemyHealth, bool& enemyActive, Keys& keys, int& gameState
)
{
    ShipUpdateActions(self, keys, gameState);
    ShipUpdateVelocity(self);
    ShipUpdatAcceleration(self);
    ShipUpdateTicks(self);
    ShipUpdateCollisionWithShip(self, ship);
    ShipUpdateCollisionWithAstroids(self, asters);
    ShipUpdateBullets(self, ship, asters, enemyRect, enemyActive, enemyHealth);
    
    EngineUpdate(self.engine);

    boundScreen(self.tex.dstrect);
}

void ShipDraw(Ship& self, int gameState)
{
    SDL_RenderCopyEx(ren, self.tex.tex, NULL, &self.tex.dstrect, self.tex.angle, NULL, SDL_FLIP_NONE);
    EngineDraw(self.engine, self, self.acts.up);
    BulletsDraw(self.bullets);
    HealthDraw(self.health);

    if (gameState != GAME_STATE_SEAT)
        ScoreDraw(self.score);
}

SDL_FPoint getMiddlePointBetweenShips(Ship& s1, Ship& s2, int coeff)
{
    Vec vec;
    SDL_Point center1 = getRectCenter(s1.tex.dstrect);
    SDL_Point center2 = getRectCenter(s2.tex.dstrect);
    VecSetLenByCoords(vec, center1, center2);
    VecSetLen(vec, VecGetLen(vec) / 2);
    return { (center1.x + vec.x) / coeff, (center1.y + vec.y) / coeff };
}
