#pragma once
#include "ship.h"
#include "bullet.h"
#include "config.h"
#include "vector.h"
#include "asteroid.h"

struct Bullet
{
    Vec       vel;
    SDL_Point pos;
    unsigned  type;
    unsigned  ticks;
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
void BulletsUpdate(Bullets& self, Ship& ship, Asteroids& asters, Keys& keys);
void BulletsDraw(Bullets& self);
