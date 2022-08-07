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

			Vec vel;
			VecSetLen(vel, rand() % 10 + 10);
			VecSetDirection(vel, rand() % 360);
			self.asteroids[i][j].vel = vel;

			self.asteroids[i][j].pos = { winWdt2 + (int)pos.x, winHgt2 + (int)pos.y };
			self.asteroids[i][j].frame = 0;
			self.asteroids[i][j].lastTicks = ticks;
		}
	}
}

void AsteroidsUpdate(Asteroids& self)
{
	int sdlTicks = SDL_GetTicks();

	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		int hgt = self.texture[i].dstrect.h;
		
		for (int j = 0; j < self.num[j]; j++)
		{
			if (sdlTicks - self.asteroids[i][j].lastTicks >= 10)
			{
				self.asteroids[i][j].lastTicks = sdlTicks;

				self.asteroids[i][j].frame += 1;
				self.asteroids[i][j].frame %= self.asteroidsFrames[i];

				self.asteroids[i][j].srcrect.x = (self.asteroids[i][j].frame % self.asteroidsFrames[i]) * hgt;
				self.asteroids[i][j].srcrect.y = 0;
			}
		}
	}
}

void AsteroidsDraw(Asteroids& self)
{
	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		int hgt = self.texture[i].dstrect.h;

		for (int j = 0; j < self.num[i]; j++)
		{
			SDL_Rect srcrect = { self.asteroids[i][j].srcrect.x, self.asteroids[i][j].srcrect.y, hgt, hgt };
			SDL_Rect dstrect = { self.asteroids[i][j].pos.x, self.asteroids[i][j].pos.y, hgt, hgt };

			SDL_RenderCopyEx(ren, self.texture[i].tex, &srcrect, &dstrect, 0, 0, SDL_FLIP_NONE);
		}
	}
}

void AsteroidsDestroy(Game& game)
{

}