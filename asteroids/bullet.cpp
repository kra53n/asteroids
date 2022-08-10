#include <SDL.h>
#include <malloc.h>

#include "bullet.h"
#include "structs.h"

void BulletsUpdate(Bullets& self, Ship& ship, KeysStatus& keys)
{
    if (keys.space)
    {
        Vec vel;
        BulletsPush(self, vel, 0);
    }
}

void BulletsDraw(Bullets& self)
{

}

void BulletsClear(Bullets& self)
{
	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
	{
		free(cur);
	}
	self.head = NULL;
}

void BulletsPush(Bullets& self, Vec vel, int type)
{
	Bullet* elem = (Bullet*)malloc(sizeof(Bullet));
	elem->vel = vel;
	elem->type = type;

	for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
	{
		if (cur->next == NULL)
		{
			elem->next = cur->next;
			cur->next = elem;
			break;
		}
	}

	if (self.head == NULL)
	{
		elem->next = NULL;
		self.head = elem;
	}
}
