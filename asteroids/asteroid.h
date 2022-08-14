#pragma once
#include "config.h"
#include "structs.h"
#include "texture.h"

void AsteroidsInit(Asteroids& self, int asteroidsTpyesNum[ASTEROIDS_TYPE_NUM]);
void AsteroidsDestroy(Asteroids& self);

void AsteroidsPush(Asteroids& self, int type, int ticks);
void AsteroidsDelAsteroid(Asteroids& self, Asteroid* aster);
void AsteroidsUpdate(Asteroids& self);
void AsteroidsDraw(Asteroids& self);
