#include <malloc.h>
#include <stdio.h>

#include "structs.h"
#include "texture.h"
#include "asteroid.h"
#include "constants.h"

void AsteroidsInit(Game& game)
{
	int ticks = SDL_GetTicks();

	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		game.asteroids.texture[i] = loadTexture(ASTEROIDS_FILENAMES[i]);
		game.asteroids.asteroidsFrames[i] = game.asteroids.texture[i].w / game.asteroids.texture[i].h;

		game.asteroids.num[i] = 1;
		game.asteroids.asteroids[i] = (Asteroid*)malloc(sizeof(Asteroid) * game.asteroids.num[i]);
		if (!game.asteroids.asteroids[i]) { exit(1); }

		for (int j = 0; j < game.asteroids.num[i]; j++)
		{
			game.asteroids.asteroids[i][j].pos = { 256, 256 };
			game.asteroids.asteroids[i][j].frame = 0;
			game.asteroids.asteroids[i][j].lastTicks = ticks;
		}
	}
}

void AsteroidsUpdate(Game& game)
{
	int sdlTicks = SDL_GetTicks();

	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		int hgt = game.asteroids.texture[i].dstrect.h;
		
		for (int j = 0; j < game.asteroids.num[j]; j++)
		{
			if (sdlTicks - game.asteroids.asteroids[i][j].lastTicks >= 10)
			{
				game.asteroids.asteroids[i][j].lastTicks = sdlTicks;
				
				game.asteroids.asteroids[i][j].frame += 1;
				game.asteroids.asteroids[i][j].frame %= game.asteroids.asteroidsFrames[i];

				game.asteroids.asteroids[i][j].srcrect.x = (game.asteroids.asteroids[i][j].frame % game.asteroids.asteroidsFrames[i]) * hgt;
				game.asteroids.asteroids[i][j].srcrect.y = 0;
			}
		}
	}
}

void AsteroidsDraw(Game& game)
{
	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		int hgt = game.asteroids.texture[i].dstrect.h;

		for (int j = 0; j < game.asteroids.num[i]; j++)
		{
			SDL_Rect srcrect = { game.asteroids.asteroids[i][j].srcrect.x, game.asteroids.asteroids[i][j].srcrect.y, hgt, hgt };
			SDL_Rect dstrect = { game.asteroids.asteroids[i][j].pos.x, game.asteroids.asteroids[i][j].pos.y, hgt, hgt };

			SDL_RenderCopyEx(ren, game.asteroids.texture[i].tex, &srcrect, &dstrect, 0, 0, SDL_FLIP_NONE);
		}
	}
}

void AsteroidsDestroy(Game& game)
{

}