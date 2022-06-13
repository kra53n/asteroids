#pragma once
#include "texture.h"
#include "constants.h"

struct Asteroid {
	Texture textures[ASTEROIDS_FRAMES_NUM];
};

void AsteroidInit();