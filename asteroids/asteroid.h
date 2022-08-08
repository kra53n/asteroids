#pragma once
#include "config.h"
#include "structs.h"
#include "texture.h"

void AsteroidsInit(Asteroids& self, int asteroidsTpyesNum[ASTEROIDS_TYPE_NUM]);
void AsteroidsDestroy(Asteroids& self);

void AsteroidsUpdate(Asteroids& self);
void AsteroidsDraw(Asteroids& self);