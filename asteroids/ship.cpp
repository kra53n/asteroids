#include <SDL.h>
#include <math.h>
#include <stdio.h>

#include "ship.h"
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
    self.bulletType = 1;
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

    self.acc = { 0, 0 };
    self.vel = { 0, 0 };
    self.rotationPower = 0;
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
    if (fabs(self.vel.x) > self.maxSpeed)
        self.vel.x = self.vel.x > 0 ? self.maxSpeed : -self.maxSpeed;
    if (fabs(self.vel.y) > self.maxSpeed)
        self.vel.y = self.vel.y > 0 ? self.maxSpeed : -self.maxSpeed;

    self.tex.dstrect.x += self.vel.x;
    self.tex.dstrect.y -= self.vel.y;
}

void ShipUpdatAcceleration(Ship& self)
{
    if (self.acts.up)
    {
        self.acc = { 0.6, 0 };
        VecSetAngle(self.acc, self.tex.angle);
        VecSumCoords(self.vel, self.acc);
    }
}

void ShipUpdateTicks(Ship& self)
{
    int ticks = SDL_GetTicks();
    if (ticks - self.ticks >= 1000)
    {
        self.ticks = ticks;

        if (self.acts.up)
        {
            int sign = self.rotationPower > 0 ? -1 : 1;
            self.rotationPower += sign * self.rotationCoeff;
        }
        else
        {
            self.vel.x /= 1.8;
            self.vel.y /= 1.8;
        }
    }
}

void ShipUpdateCollisionWithAstroids(Ship& self, Asteroids& asters)
{
    int shipR = self.tex.dstrect.w > self.tex.dstrect.h ? self.tex.dstrect.h : self.tex.dstrect.w;
    shipR /= 2;
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

        if (!isCircsColliding(shipPoint, shipR, asterPoint, asterR)) continue;
        
        VecSetAngleByCoords(self.vel, asterPoint, shipPoint);
        VecSetAngleByCoords(aster->vel, shipPoint, asterPoint);

        float asterRebound = 60 / ASTEROIDS[aster->type].mass;
        float shipRebound = 70 / asterRebound;
        asterRebound /= shipR / 10;
        asterRebound *= shipR / 10;

        VecSetLen(self.vel, 70 / asterRebound);
        VecSetLen(aster->vel, asterRebound);
        
        HealthUpdate(self.health, ASTEROIDS[aster->type].damage);
        aster->health -= 10;
    }
}

void ShipShoot(Ship& self, int type)
{
    int ticks = SDL_GetTicks();
    if (ticks - self.bullets.ticks < BULLETS[type].delay) return;
    self.bullets.ticks = ticks;

    switch (type)
    {
    case 0:
        BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);
        break;

    case 1:
        for (float i = 0; i < 350; i += 0.1)
        {
            Bullet* bullet = BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);

            Vec pos;
            VecSetLen(pos, VecGetLen(bullet->vel) * i);
            VecSetAngle(pos, -VecGetAngle(bullet->vel));

            bullet->pos.x += pos.x;
            bullet->pos.y += pos.y;
        }
        break;

    case 2:
        for (int angle = -45; angle < 45; angle += 15)
        {
            Bullet* bullet = BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);
            VecSetAngle(bullet->vel, VecGetAngle(bullet->vel) - angle);
        }
        break;

    case 3:
        for (int angle = -180; angle < 180; angle += 30)
        {
            Bullet* bullet = BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);

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
        getRadius(ship.tex.dstrect),
        { bullet->pos.x, bullet->pos.y }
    )) return false;
    
    ship.health.point -= BULLETS[bullet->type].damage;
    HealthUpdate(ship.health, BULLETS[bullet->type].damage);
    BulletsDelBullet(self.bullets, bullet);

    return true;
}

void ShipBulletsUpdate(Ship& self, Ship& ship, Asteroids& asters,
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

    if (!isCircsColliding(
        s1Center, getRadius(self.tex.dstrect),
        s2Center, getRadius(self.tex.dstrect)
    )) return;
    
    HealthUpdate(self.health, SHIP_DAMAGE);
    HealthUpdate(ship.health, SHIP_DAMAGE);

    VecSetAngleByCoords(self.vel, s2Center, s1Center);
    VecSetAngleByCoords(ship.vel, s1Center, s2Center);
    
    float maxVel = max(VecGetLen(self.vel), VecGetLen(ship.vel));
    VecSetLen(self.vel, maxVel);
    VecSetLen(ship.vel, maxVel);
}

void ShipUpdate(Ship& self, Ship& ship, Asteroids& asters, SDL_Rect& enemyRect,
    Health& enemyHealth, bool& enemyActive, Keys& keys, int& gameState
)
{
    ShipUpdateActions(self, keys, gameState);

    int sign = 0;
    if (self.acts.left)  sign = -1;
    if (self.acts.right) sign = 1;
    self.tex.angle += self.rotationPower;

    if (self.acts.up && sign)
    {
        self.tex.angle += sign * self.rotationSpeed;
        self.rotationPower = sign * 1.4;
    }

    ShipUpdateVelocity(self);
    ShipUpdatAcceleration(self);
    ShipUpdateTicks(self);
    ShipUpdateCollisionWithShip(self, ship);
    ShipUpdateCollisionWithAstroids(self, asters);
    ShipBulletsUpdate(self, ship, asters, enemyRect, enemyActive, enemyHealth);
    
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

    // int side = self.tex.dstrect.w > self.tex.dstrect.h ? self.tex.dstrect.h : self.tex.dstrect.w;
    // Vec line = { side / 2, 0 };
    // int x1 = self.tex.dstrect.x + side / 2;
    // int y1 = self.tex.dstrect.y + side / 2;

    // SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
    // for (int i = 0; i < 360; i += 15)
    // {
    //     VecSetAngle(line, i);
    //     int x2 = x1 + line.x;
    //     int y2 = y1 + line.y;
    //     SDL_RenderDrawLine(ren, x1, y1, x2, y2);
    // }
    // SDL_RenderDrawRect(ren, &self.tex.dstrect);
}
