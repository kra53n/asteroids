#include <SDL.h>
#include <math.h>
#include <stdio.h>

#include "ship.h"
#include "score.h"
#include "funcs.h"
#include "enemy.h"
#include "bullet.h"
#include "vector.h"
#include "window.h"
#include "health.h"
#include "config.h"
#include "texture.h"
#include "structs.h"
#include "animation.h"

void EngineUpdate(Animation& self, Keys& keys)
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
    VecSetDirection(pos, -ship.tex.angle);

    SDL_Rect dstrect = self.textures->dstrect;
    dstrect.x = ship.tex.dstrect.x + (ship.tex.dstrect.w - self.textures->dstrect.w) / 2 - pos.x;
    dstrect.y = ship.tex.dstrect.y + (ship.tex.dstrect.h - self.textures->dstrect.h) / 2 - pos.y;

    SDL_RenderCopyEx(ren, self.textures[self.frame].tex, 0, &dstrect, ship.tex.angle, 0, SDL_FLIP_NONE);
}

void ShipInit(Ship& self)
{
    self.ticks = SDL_GetTicks();
    self.ticks = self.ticks;
    self.tex = loadTexture(SHIP_FILENAME);

    self.tex.dstrect.w *= SHIP_SCALE_COEFF;
    self.tex.dstrect.h *= SHIP_SCALE_COEFF;

    self.tex.dstrect.x = (winWdt - self.tex.dstrect.w) / 2;
    self.tex.dstrect.y = (winHgt - self.tex.dstrect.h) / 2;

    AnimationInit(self.engine, ENGINE_FRAMES, ENGINE_FILENAME, ENGINE_FILENAME_TYPE, SHIP_SCALE_COEFF);
    ScoreInit(self.score, { 10, 3 }, 0, (char*)"Score: ");
    HealthInit(self.health, { 10, 50, 250, 25 });
    BulletsInit(self.bullets);
}

void ShipUpdateVelocity(Ship& self, Keys& keys)
{
    if (fabs(self.vel.x) > self.maxSpeed)
        self.vel.x = self.vel.x > 0 ? self.maxSpeed : -self.maxSpeed;
    if (fabs(self.vel.y) > self.maxSpeed)
        self.vel.y = self.vel.y > 0 ? self.maxSpeed : -self.maxSpeed;

    self.tex.dstrect.x += self.vel.x;
    self.tex.dstrect.y -= self.vel.y;
}

void ShipUpdatAcceleration(Ship& self, Keys& keys)
{
    if (keys.up)
    {
        self.acc = { 0.6, 0 };
        VecSetDirection(self.acc, self.tex.angle);
        VecSumCoords(self.vel, self.acc);
    }
}

void ShipUpdateTicks(Ship& self, Keys& keys)
{
    int ticks = SDL_GetTicks();
    if (ticks - self.ticks >= 1000)
    {
        self.ticks = ticks;

        if (keys.up)
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
        
        VecSetDirectionByCoords(self.vel, asterPoint, shipPoint);
        VecSetDirectionByCoords(aster->vel, shipPoint, asterPoint);

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
    if (!(ticks - self.bullets.ticks >= BULLETS[type].delay)) return;
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
            VecSetDirection(pos, -VecGetAngle(bullet->vel));

            bullet->pos.x += pos.x;
            bullet->pos.y += pos.y;
        }
        break;

    case 2:
        for (int angle = -45; angle < 45; angle += 15)
        {
            Bullet* bullet = BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);
            VecSetDirection(bullet->vel, VecGetAngle(bullet->vel) - angle);
        }
        break;

    case 3:
        for (int angle = -180; angle < 180; angle += 30)
        {
            Bullet* bullet = BulletsPush(self.bullets, self.tex, type, BULLET_PLAYER1_AFFILIATION);

            Vec pos;
            VecSetLen(pos, self.tex.dstrect.w);
            VecSetDirection(pos, VecGetAngle(bullet->vel) - angle);

            bullet->pos = getRectCenter(self.tex.dstrect);
            bullet->pos.x += pos.x;
            bullet->pos.y += pos.y;

            VecSetDirection(bullet->vel, VecGetAngle(bullet->vel) + angle);
        }
        break;
    }
}

bool ShipUpdateBulletCollisionWithEnemy(Ship& self, SDL_Rect& enemyRect, Health& enemyHealth, Bullet* bullet)
{
	if (!isPointInCirc(
		getRectCenter(enemyRect),
		getRadius(enemyRect),
		{ bullet->pos.x, bullet->pos.y }
	)) return false;
	
	enemyHealth.point -= BULLETS[bullet->type].damage;
	if (enemyHealth.point <= 0)
	{
		ScoreUpdate(self.score, ENEMY_HEALTH);
	}
	BulletsDelBullet(self.bullets, bullet);

    return true;
}

void ShipBulletsUpdate(Ship& self, Asteroids& asters, SDL_Rect& enemyRect, Health& enemyHealth, Keys& keys)
{
    for (Bullet* cur = self.bullets.head; cur != NULL;)
    {
        Bullet* curNext = cur->next;

        cur->pos.x += cur->vel.x;
        cur->pos.y -= cur->vel.y;

        if (BulletsUpdateCollisionWithAstroids(self.bullets, cur, asters, self.score) ||
            ShipUpdateBulletCollisionWithEnemy(self, enemyRect, enemyHealth, cur))
        {
            cur = curNext;
            continue;
        }

        if (cur->pos.x < 0 || cur->pos.x > winWdt || 
            cur->pos.y < 0 || cur->pos.y > winHgt)
        {
            BulletsDelBullet(self.bullets, cur);
        }

        cur = curNext;
    }

    if (!keys.space) return;

    ShipShoot(self, 1);
}

void ShipUpdate(Ship& self, Asteroids& asters, SDL_Rect& enemyRect, Health& enemyHealth, Keys& keys, int& gameState)
{
    int sign = 0;
    if (keys.left)  sign = -1;
    if (keys.right) sign = 1;
    self.tex.angle += self.rotationPower;

    if (keys.up && sign)
    {
        self.tex.angle += sign * self.rotationSpeed;
        self.rotationPower = sign * 1.4;
    }

    ShipUpdateVelocity(self, keys);
    ShipUpdatAcceleration(self, keys);
    ShipUpdateTicks(self, keys);
    ShipUpdateCollisionWithAstroids(self, asters);
    ShipBulletsUpdate(self, asters, enemyRect, enemyHealth, keys);
    
    EngineUpdate(self.engine, keys);

    boundScreen(self.tex.dstrect);

    if (self.health.point <= 0)
        gameState = GAME_STATE_RESTART;
}

void ShipDraw(Ship& self, Keys& keys)
{
    SDL_RenderCopyEx(ren, self.tex.tex, NULL, &self.tex.dstrect, self.tex.angle, NULL, SDL_FLIP_NONE);
    EngineDraw(self.engine, self, keys.up);
    ScoreDraw(self.score);
    HealthDraw(self.health);
    BulletsDraw(self.bullets);

     // int side = self.tex.dstrect.w > self.tex.dstrect.h ? self.tex.dstrect.h : self.tex.dstrect.w;
     // Vec line = { side / 2, 0 };
     // int x1 = self.tex.dstrect.x + side / 2;
     // int y1 = self.tex.dstrect.y + side / 2;

     // SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
     // for (int i = 0; i < 360; i += 15)
     // {
     //     VecSetDirection(line, i);
     //     int x2 = x1 + line.x;
     //     int y2 = y1 + line.y;
     //     SDL_RenderDrawLine(ren, x1, y1, x2, y2);
     // }
     // SDL_RenderDrawRect(ren, &self.tex.dstrect);
}
