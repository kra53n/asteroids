#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "config.h"
#include "window.h"
#include "vector.h"
#include "structs.h"
#include "texture.h"
#include "asteroid.h"
#include "animation.h"

void ExplosionUpdate(Asteroids& self)
{
	if (!self.explosion.frame) return;

	int ticks = SDL_GetTicks();
	if (!(ticks- self.explosion.ticks >= EXPLOSION_DELAY)) return;
	self.explosion.ticks = ticks;

	self.explosion.frame = self.explosion.frame < EXPLOSION_FRAMES - 1 ? ++self.explosion.frame : 0;
}

void ExplosionDraw(Asteroids& self)
{
	if (!self.explosion.frame) return;

	SDL_Rect dstrect = self.explosion.textures[self.explosion.frame].dstrect;
	dstrect.x = self.explosionPos.x;
	dstrect.y = self.explosionPos.y;

	SDL_RenderCopy(ren, self.explosion.textures[self.explosion.frame].tex, 0, &dstrect);
}

int AsteroidsGetNum(int asteroidTypeNums[ASTEROIDS_TYPE_NUM])
{
	int num = 0;
	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
		num += asteroidTypeNums[i];
	return num;
}

Asteroid* AsteroidsGetNewAsteroid(Asteroids& self, int type, int ticks)
{
	Asteroid* elem = (Asteroid*)malloc(sizeof(Asteroid));

    Vec pos;
    int offset = 250;
    VecSetLen(pos, (rand() % (winWdt2 - offset)) + offset);
    VecSetDirection(pos, rand() % 360);

    VecSetLen(elem->vel, rand() % 5 + 5);
    VecSetDirection(elem->vel, rand() % 360);

    elem->pos = { winWdt2 + (int)pos.x, winHgt2 + (int)pos.y };
    elem->frame = 0;
    elem->ticks = ticks;

	elem->type = type;
	elem->next = NULL;

	return elem;
}

void AsteroidsPush(Asteroids& self, int type, int ticks)
{
	Asteroid* elem = AsteroidsGetNewAsteroid(self, type, ticks);

	for (Asteroid* cur = self.head; cur != NULL; cur = cur->next)
	{
		if (cur->next == NULL)
		{
			elem->prev = cur;
			cur->next = elem;
			break;
		}
	}

	if (self.head == NULL)
	{
		elem->prev = NULL;
		self.head = elem;
	}
}

void AsteroidsDelAsteroid(Asteroids& self, Asteroid* aster)
{
	if (aster->next == NULL)
	{
		if (aster->prev == NULL)
			self.head = NULL;
		else
			aster->prev->next = NULL;
	}
	else if (self.head == aster)
	{
		self.head = aster->next;
		self.head->prev = NULL;
	}
	else
	{
		aster->prev->next = aster->next;
		aster->next->prev = aster->prev;
	}

	self.explosionPos = { aster->pos.x, aster->pos.y };
	self.explosion.frame = 1;
	free(aster);
}

void AsteroidsInit(Asteroids& self, int asteroidTypeNums[ASTEROIDS_TYPE_NUM])
{
	int ticks = SDL_GetTicks();

	for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
	{
		self.texture[i] = loadTexture(ASTEROIDS_FILENAMES[i]);
		self.frames[i] = self.texture[i].dstrect.w / self.texture[i].dstrect.h;
	}

	int num = AsteroidsGetNum(asteroidTypeNums);

    for (int i = 0, asterType = 0, asterTypeIndex = 0; i < num; i++)
    {
        AsteroidsPush(self, asterType, ticks);

        asterTypeIndex++;
        if (asteroidTypeNums[asterType] == asterTypeIndex)
        {
            asterTypeIndex = 0;
            asterType++;
        }
    }

	AnimationInit(self.explosion, EXPLOSION_FRAMES, EXPLOSION_FILENAME, EXPLOSION_FILENAME_TYPE, EXPLOSION_SCALE_COEFF);
}

void AsteroidsDestroy(Asteroids& self)
{
	for (Asteroid* aster = self.head; aster != NULL; aster = aster->next)
	{
		free(aster);
	}
	self.head = NULL;
}

void AsteroidsUpdate(Asteroids& self)
{
	int sdlTicks = SDL_GetTicks();

    for (Asteroid* aster = self.head; aster != NULL; aster = aster->next)
	{
		int hgt = self.texture[aster->type].dstrect.h;
		
		bool timeSpent = sdlTicks - aster->ticks >= 10;
		if (!timeSpent) continue;

		aster->ticks = sdlTicks;

		aster->frame += 1;
		aster->frame %= self.frames[aster->type];

		aster->pos.x += aster->vel.x;
		aster->pos.y += aster->vel.y;

		aster->srcrect.x = (aster->frame % self.frames[aster->type]) * hgt;
		aster->srcrect.y = 0;

		SDL_Rect rect = { aster->pos.x, aster->pos.y, hgt, hgt };
		boundScreen(rect);
		aster->pos.x = rect.x;
		aster->pos.y = rect.y;
	}

	ExplosionUpdate(self);
}

void AsteroidsDraw(Asteroids& self)
{
    for (Asteroid* aster = self.head; aster != NULL; aster = aster->next)
    {
		int asterType = aster->type;
 		int hgt = self.texture[aster->type].dstrect.h;
 
		SDL_Rect srcrect = { aster->srcrect.x, aster->srcrect.y, hgt, hgt };
		SDL_Rect dstrect = { aster->pos.x,     aster->pos.y,     hgt, hgt };

		SDL_RenderCopyEx(ren, self.texture[aster->type].tex, &srcrect, &dstrect, 0, 0, SDL_FLIP_NONE);
    }

	ExplosionDraw(self);
 }
