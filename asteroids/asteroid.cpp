#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "config.h"
#include "window.h"
#include "vector.h"
#include "structs.h"
#include "texture.h"
#include "asteroid.h"

int AsteroidsGetNum(int asteroidTypeNums[ASTEROIDS_TYPE_NUM])
{
	int num = 0;
	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
		num += asteroidTypeNums[i];
	return num;
}

void AsteroidsCreateByNum(Asteroids& self, int ticks)
{
	for (int i = 0; i < self.num; i++)
	{
		Vec pos;
		int offset = 250;
		VecSetLen(pos, (rand() % (winWdt2 - offset)) + offset);
		VecSetDirection(pos, rand() % 360);

		Vec vel;
		VecSetLen(vel, rand() % 5 + 5);
		VecSetDirection(vel, rand() % 360);
		self.asteroids[i].vel = vel;

		self.asteroids[i].pos = { winWdt2 + (int)pos.x, winHgt2 + (int)pos.y };
		self.asteroids[i].frame = 0;
		self.asteroids[i].lastTicks = ticks;
		self.asteroids[i].lastTicks = true;
	}

}

// asteroidsTypes - array of bool that show how many asteroids will be
void AsteroidsInit(Asteroids& self, int asteroidTypeNums[ASTEROIDS_TYPE_NUM])
{
	int ticks = SDL_GetTicks();

	self.num = AsteroidsGetNum(asteroidTypeNums);
	self.asteroids = (Asteroid*)malloc(sizeof(Asteroid) * self.num);
	if (!self.asteroids) { deInit(1); }

	int asteroidIndex = 0;
	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		self.texture[i] = loadTexture(ASTEROIDS_FILENAMES[i]);
		self.asteroidsFrames[i] = self.texture[i].w / self.texture[i].h;

		int j;
		for (j = 0; j < asteroidTypeNums[i]; j++)
		{
			self.asteroids[asteroidIndex + j].asteroidType = i;
		}
		asteroidIndex += j;
	}

    AsteroidsCreateByNum(self, ticks);
}

void AsteroidsDestroy(Asteroids& self)
{
	free(self.asteroids);
}

// void AsteroidsUpdateCollision(Asteroids& self)
// {
// 	int asterType, asterR;
// 
// 	for (int i = 0; i < self.num; i++)
// 	{
// 		asterType = self.asteroids[i].asteroidType;
// 		asterR = self.texture[asterType].dstrect.h / 2;
// 		SDL_Point asterPoint1 = {
// 			self.asteroids[i].pos.x + asterR,
// 			self.asteroids[i].pos.y + asterR
// 		};
// 
// 		for (int j = 0; j < self.num; j++)
// 		{
// 			if (i == j) continue;
// 
// 			asterType = self.asteroids[j].asteroidType;
// 			asterR = self.texture[asterType].dstrect.h / 2;
// 			SDL_Point asterPoint2 = {
// 				self.asteroids[j].pos.x + asterR,
// 				self.asteroids[j].pos.y + asterR
// 			};
// 			
// 			VecSetDirectionByCoords(self.asteroids[i].vel, asterPoint2, asterPoint1);
// 			VecSetDirectionByCoords(self.asteroids[j].vel, asterPoint1, asterPoint2);
// 			VecSetLen(self.asteroids[i].vel, 10);
// 			VecSetLen(self.asteroids[j].vel, 10);
// 		}
// 	}
// }

void AsteroidsUpdate(Asteroids& self)
{
	int sdlTicks = SDL_GetTicks();

	for (int i = 0; i < self.num; i++)
	{
		int asterType = self.asteroids[i].asteroidType;
		int hgt = self.texture[asterType].dstrect.h;
		
		bool timeSpent = sdlTicks - self.asteroids[i].lastTicks >= 10;
		if (!timeSpent) continue;

		self.asteroids[i].lastTicks = sdlTicks;

		self.asteroids[i].frame += 1;
		self.asteroids[i].frame %= self.asteroidsFrames[i];

		self.asteroids[i].pos.x += self.asteroids[i].vel.x;
		self.asteroids[i].pos.y += self.asteroids[i].vel.y;

		self.asteroids[i].srcrect.x = (self.asteroids[i].frame % self.asteroidsFrames[asterType]) * hgt;
		self.asteroids[i].srcrect.y = 0;

		SDL_Rect rect = {self.asteroids[i].pos.x, self.asteroids[i].pos.y, hgt, hgt};
		boundScreen(rect);
		self.asteroids[i].pos.x = rect.x;
		self.asteroids[i].pos.y = rect.y;
	}
}

void AsteroidsDraw(Asteroids& self)
{
	for (int i = 0; i < self.num; i++)
 	{
		int asterType = self.asteroids[i].asteroidType;
 		int hgt = self.texture[asterType].dstrect.h;
 
		SDL_Rect srcrect = { self.asteroids[i].srcrect.x, self.asteroids[i].srcrect.y, hgt, hgt };
		SDL_Rect dstrect = { self.asteroids[i].pos.x, self.asteroids[i].pos.y, hgt, hgt };

		SDL_RenderCopyEx(ren, self.texture[asterType].tex, &srcrect, &dstrect, 0, 0, SDL_FLIP_NONE);
 	}
 }
