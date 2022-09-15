#pragma once
#include "score.h"
#include "bullet.h"
#include "config.h"
#include "vector.h"
#include "asteroid.h"

struct Bullet
{
    Vec       vel;
    SDL_Point pos;
    int       type;
    int       ticks;
    int       affiliation;
    Bullet*   next;
    Bullet*   prev;
};

struct Bullets
{
    Bullet*  head                    = 0;
    Texture  texs[BULLETS_TYPE_NUM];
    unsigned ticks                   = 0;
};

void BulletsInit(Bullets& self);
void BulletsDestroy(Bullets& self);

void BulletsDelBullet(Bullets& self, Bullet* bullet);
bool BulletsUpdateCollisionWithAstroids(Bullets& self, Bullet* bullet, Asteroids& asters, Score& score);
Bullet* BulletsPush(Bullets& self, Texture& tex, int type);

void BulletsDraw(Bullets& self);
