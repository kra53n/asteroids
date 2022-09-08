#pragma once
#include "ship.h"
#include "health.h"
#include "config.h"
#include "vector.h"
#include "bullet.h"
#include "texture.h"

struct Enemy
{
    Texture tex;
    Bullets bullets;
    Health  health;
    Vec     vel         = { 0, 0 };
    Vec     acc         = { 0, 0 };
    int     damage      = ENEMY_DAMAGE;
    int     ticks;
    int     damageTicks;
    bool    active;
};

void EnemyInit(Enemy& self);
void EnemyDestroy(Enemy& self);

void EnemyUpdate(Enemy& self, Ship& ship);
void EnemyDraw(Enemy& self);
