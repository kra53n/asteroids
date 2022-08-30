#include <SDL.h>
#include <stdio.h>
#include <malloc.h>

#include "score.h"
#include "funcs.h"
#include "vector.h"
#include "window.h"
#include "config.h"
#include "bullet.h"
#include "asteroid.h"

void BulletsInit(Bullets& self)
{
	for (int i = 0; i < BULLETS_TYPE_NUM; i++)
	{
		self.texs[i] = loadTexture(BULLETS[i].filename);
		self.texs[i].dstrect.w *= SHIP_SCALE_COEFF;
		self.texs[i].dstrect.h *= SHIP_SCALE_COEFF;
	}
}

void BulletsDestroy(Bullets& self)
{
	for (int i = 0; i < BULLETS_TYPE_NUM; i++)
	{
		SDL_DestroyTexture(self.texs[i].tex);
	}
}

void BulletsClear(Bullets& self)
{
	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
	{
		free(cur);
	}
	self.head = NULL;
}

Bullet* BulletsGetNewBullet(Bullets& self, Texture& tex, int type, int affiliation)
{
	Bullet* elem = (Bullet*)malloc(sizeof(Bullet));

	if (!elem)
	{
		printf("\nMemory allocation error in BulletsGetNewBullet");
		deInit(1);
	}

	VecSetLen(elem->vel, BULLETS[type].speed);
	VecSetDirection(elem->vel, tex.angle);

	Vec pos;
	VecSetLen(pos, tex.dstrect.w / 2);
	VecSetDirection(pos, -tex.angle);

	elem->pos = {
		(int)(tex.dstrect.x + tex.dstrect.w / 2 + pos.x),
		(int)(tex.dstrect.y + tex.dstrect.h / 2 + pos.y),
	};

	elem->ticks = SDL_GetTicks();
	elem->affiliation = affiliation;
	elem->type = type;
	elem->next = NULL;

	return elem;
}

Bullet* BulletsPush(Bullets& self, Texture& tex, int type, int affiliation)
{
	Bullet* elem = BulletsGetNewBullet(self, tex, type, affiliation);

	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
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

	return elem;
}

void BulletsDelBullet(Bullets& self, Bullet* bullet)
{
	if (bullet->next == NULL)
	{
		if (bullet->prev == NULL)
			self.head = NULL;
		else
			bullet->prev->next = NULL;
	}
	else if (self.head == bullet)
	{
		self.head = bullet->next;
		self.head->prev = NULL;
	}
	else
	{
		bullet->prev->next = bullet->next;
		bullet->next->prev = bullet->prev;
	}

	free(bullet);
}

// return status of collision
bool BulletsUpdateCollisionWithAstroids(Bullets& self, Bullet* bullet, Asteroids& asters, Score& score)
{
	for (Asteroid* aster = asters.head; aster != NULL; aster = aster->next)
	{
		int asterR = asters.texture[aster->type].dstrect.h / 2;

        bool cond = isPointInCirc(
            { aster->pos.x + asterR, aster->pos.y + asterR },
            asterR,
            { bullet->pos.x, bullet->pos.y }
        );
        if (!cond) continue;
		
		aster->health -= BULLETS[bullet->type].damage;
		if (aster->health <= 0)
		{
			ScoreUpdate(score, ASTEROIDS[aster->type].health);
			AsteroidsDelAsteroid(asters, aster);
		}
        BulletsDelBullet(self, bullet);

		return true;
	}
}

// NOTE: move to ship.cpp
void BulletsAddByType(Bullets& self, Ship& ship, int type)
{
	int ticks = SDL_GetTicks();
	if (!(ticks - self.ticks >= BULLETS[type].delay)) return;
	self.ticks = ticks;

	switch (type)
	{
	case 0:
		BulletsPush(self, ship.tex, type, BULLET_PLAYER1_AFFILIATION);
		break;

	case 1:
		for (float i = 0; i < 350; i += 0.1)
		{
			Bullet* bullet = BulletsPush(self, ship.tex, type, BULLET_PLAYER1_AFFILIATION);

			Vec pos;
			VecSetLen(pos, VecGetLen(bullet->vel) * i);
			VecSetDirection(pos, -VecGetAngle(bullet->vel));

			bullet->pos.x += pos.x;
			bullet->pos.y += pos.y;
		}
		break;

	case 2:
		for (int angle = -45; angle < 45; angle += 15)
		{
			Bullet* bullet = BulletsPush(self, ship.tex, type, BULLET_PLAYER1_AFFILIATION);
			VecSetDirection(bullet->vel, VecGetAngle(bullet->vel) - angle);
		}
		break;

	case 3:
		for (int angle = -180; angle < 180; angle += 30)
		{
			Bullet* bullet = BulletsPush(self, ship.tex, type, BULLET_PLAYER1_AFFILIATION);

			Vec pos;
			VecSetLen(pos, ship.tex.dstrect.w);
			VecSetDirection(pos, VecGetAngle(bullet->vel) - angle);

			bullet->pos.x = ship.tex.dstrect.x + ship.tex.dstrect.w / 2 + pos.x;
			bullet->pos.y = ship.tex.dstrect.y + ship.tex.dstrect.h / 2 + pos.y;

			VecSetDirection(bullet->vel, VecGetAngle(bullet->vel) + angle);
		}
		break;
	}
}

void BulletsUpdate(Bullets& self, Ship& ship, Asteroids& asters, Keys& keys)
{
	for (Bullet* cur = self.head; cur != NULL;)
	{
		Bullet* curNext = cur->next;

		cur->pos.x += cur->vel.x;
		cur->pos.y -= cur->vel.y;

		if (BulletsUpdateCollisionWithAstroids(self, cur, asters, ship.score))
		{
			cur = curNext;
			continue;
		}

		if (cur->pos.x < 0 || cur->pos.x > winWdt || 
		    cur->pos.y < 0 || cur->pos.y > winHgt)
		{
			BulletsDelBullet(self, cur);
		}

		cur = curNext;
	}

	if (!keys.space) return;

	BulletsAddByType(self, ship, 1);
}

void BulletsDraw(Bullets& self)
{
	SDL_Point nullPoint = { 0, 0 };

	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
	{
		Texture tex = self.texs[cur->type];
		SDL_Rect rect = { cur->pos.x, cur->pos.y, tex.dstrect.w, tex.dstrect.h };
		SDL_RenderCopyEx(ren, tex.tex, 0, &rect, VecGetAngle(cur->vel), 0, SDL_FLIP_NONE);
	}
}
