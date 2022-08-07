#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "config.h"
#include "vector.h"
#include "structs.h"
#include "texture.h"
#include "asteroid.h"

void AsteroidsInit(Asteroids& self)
{
	int ticks = SDL_GetTicks();

	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		self.texture[i] = loadTexture(ASTEROIDS_FILENAMES[i]);
		self.asteroidsFrames[i] = self.texture[i].w / self.texture[i].h;

		self.num[i] = rand() % 3;
		self.asteroids[i] = (Asteroid*)malloc(sizeof(Asteroid) * self.num[i]);
		if (!self.asteroids[i]) { exit(1); }

		for (int j = 0; j < self.num[i]; j++)
		{
			Vec pos;
			int offset = 250;
			VecSetLen(pos, (rand() % (winWdt2 - offset)) + offset);
			VecSetDirection(pos, rand() % 360);

			self.asteroids[i][j].pos = { winWdt2 + (int)pos.x, winHgt2 + (int)pos.y };
			self.asteroids[i][j].frame = 0;
			self.asteroids[i][j].lastTicks = ticks;
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