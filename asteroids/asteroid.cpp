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
 }
