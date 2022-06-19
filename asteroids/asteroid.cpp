#include <malloc.h>
#include <stdio.h>

#include "structs.h"
#include "texture.h"
#include "asteroid.h"
#include "constants.h"

void AsteroidsInit(Game& game)
{
	game.asteroids.texture = loadTexture(ASTEROIDS_FILENAME);
	
	game.asteroids.num = 1;
	game.asteroids.asteroids = (Asteroid*)malloc(sizeof(Asteroid) * game.asteroids.num);
	if (!game.asteroids.asteroids) { exit(1); }

	game.asteroids.asteroids[0].pos = { 256, 256 };
	game.asteroids.asteroids[0].frame = 0;
	game.asteroids.asteroids[0].lastTick = SDL_GetTicks();
}

void AsteroidsUpdate(Game& game)
{
	int sdlTicks = SDL_GetTicks();
	int hgt = game.asteroids.texture.dstrect.h;

	if (sdlTicks - game.asteroids.asteroids[0].lastTick >= 10)
	{
		game.asteroids.asteroids[0].lastTick = sdlTicks;

		game.asteroids.asteroids[0].frame -= 1;
		game.asteroids.asteroids[0].frame %= ASTEROIDS_FRAMES_NUM;

		game.asteroids.asteroids[0].srcrect.x = (game.asteroids.asteroids[0].frame % ASTEROIDS_FRAMES_NUM) * hgt;
		game.asteroids.asteroids[0].srcrect.y = 0;
	}
}

void AsteroidsDraw(Game& game)
{
	int hgt = game.asteroids.texture.dstrect.h;

	SDL_Rect srcrect = { game.asteroids.asteroids[0].srcrect.x, game.asteroids.asteroids[0].srcrect.y, hgt, hgt };
	SDL_Rect dstrect = { game.asteroids.asteroids[0].pos.x, game.asteroids.asteroids[0].pos.y, hgt, hgt };

	for (int i = 0; i < game.asteroids.num; i++)
	{
		SDL_RenderCopyEx(ren, game.asteroids.texture.tex, &srcrect, &dstrect, 0, 0, SDL_FLIP_NONE);
	}
}

void AsteroidsDestroy(Game& game)
{

}