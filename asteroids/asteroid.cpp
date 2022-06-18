#include <malloc.h>

#include "structs.h"
#include "texture.h"
#include "asteroid.h"
#include "constants.h"

void AsteroidInit(Game& game)
{
	game.asteroids.texture = loadTexture(ASTEROIDS_FILENAME);
	
	game.asteroids.asteroids = (Asteroid*)malloc(sizeof(Asteroid));
	if (!game.asteroids.asteroids) { exit(1); }

	game.asteroids.asteroids[0].pos = { 256, 256 };
}