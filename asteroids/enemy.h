#pragma once
#include "vector.h"
#include "bullet.h"
#include "texture.h"

struct Enemy
{
	Texture tex;
	Vec     vel;
	Vec     acc;
	int     health;
	int     damage;
	Bullets bullets;
};

void EnemyInit(Enemy& self);
void EnemyDestroy(Enemy& self);

void EnemyUpdate(Enemy& self);
void EnemyDraw(Enemy& self);
