#include <SDL.h>
#include <malloc.h>

#include "window.h"
#include "config.h"
#include "bullet.h"
#include "structs.h"

void BulletsInit(Bullets& self)
{
	for (int i = 0; i < BULLETS_TYPE_NUM; i++)
	{
		self.texs[i] = loadTexture(BULLETS_FILENAMES[i]);
		int coeff = 4;
		self.texs[i].dstrect.w /= coeff;
		self.texs[i].dstrect.h /= coeff;
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

void BulletsPush(Bullets& self, Vec vel, SDL_Point pos, int type)
{
	Bullet* elem = (Bullet*)malloc(sizeof(Bullet));
	elem->next = NULL;
	elem->vel = vel;
	elem->type = type;
	elem->pos = pos;

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
}

void BulletsDelBullet(Bullets& self, Bullet* bullet)
{
	if (bullet->next == NULL)
	{
		self.head = NULL;
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

void BulletsUpdate(Bullets& self, Ship& ship, KeysStatus& keys)
{
	for (Bullet* cur = self.head; cur != NULL;)
	{
		Bullet* curNext = cur->next;

		cur->pos.x += cur->vel.x;
		cur->pos.y -= cur->vel.y;

		if (cur->pos.x < 0 || cur->pos.x > winWdt || 
		    cur->pos.y < 0 || cur->pos.y > winHgt)
		{
			BulletsDelBullet(self, cur);
		}

		cur = curNext;
	}

	if (!keys.space) return;

	int type = 0;

	Vec vel = {};
	VecSetLen(vel, 30);
	VecSetDirection(vel, ship.tex.angle);

	Vec pos = { ship.tex.dstrect.w / 2, ship.tex.dstrect.h / 2 };
	VecSetLen(pos, ship.tex.dstrect.w / 2);
	VecSetDirection(pos, -ship.tex.angle);

	SDL_Point point = {
		ship.tex.dstrect.x + ship.tex.dstrect.w / 2 + pos.x,
		ship.tex.dstrect.y + ship.tex.dstrect.h / 2 + pos.y,
	};

	BulletsPush(self, vel, point, type);
}

void BulletsDraw(Bullets& self)
{
	SDL_Point nullPoint = { 0, 0 };

	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
	{
		Texture tex = self.texs[cur->type];
		SDL_Rect rect = { cur->pos.x, cur->pos.y, tex.dstrect.w, tex.dstrect.h };
		SDL_RenderCopyEx(ren, tex.tex, 0, &rect, VecGetAngle(cur->vel), &nullPoint, SDL_FLIP_NONE);
	}
}
