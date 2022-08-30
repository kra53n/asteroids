#pragma once
#include "config.h"
#include "vector.h"
#include "bullet.h"
#include "texture.h"

struct Enemy
{
	Texture tex;
	Vec     vel      = { 0, 0 };
	Vec     acc      = { 0, 0 };
	int     health   = ENEMY_HEALTH;
	int     damage   = ENEMY_DAMAGE;
	int     ticks;
};

void EnemyInit(Enemy& self);
void EnemyDestroy(Enemy& self);

void EnemyUpdate(Enemy& self, Ship& ship, Bullets& bullets);
void EnemyDraw(Enemy& self);
