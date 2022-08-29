#include <SDL.h>

#include "enemy.h"
#include "bullet.h"
#include "window.h"
#include "texture.h"

void EnemyInit(Enemy& self)
{
	self.tex = loadTexture(ENEMY_FILENAME);
	self.tex.dstrect.w *= ENEMY_SCALE_COEFF;
	self.tex.dstrect.h *= ENEMY_SCALE_COEFF;

	self.ticks = SDL_GetTicks();
}

void EnemyDestroy(Enemy& self)
{
	SDL_DestroyTexture(self.tex.tex);
	BulletsDestroy(self.bullets);
}

void EnemyUpdateMovement(Enemy& self)
{
	self.vel.x += self.acc.x;
	self.vel.y += self.acc.y;
	VecSetLen(self.acc, VecGetLen(self.acc) + 0.1);

	self.tex.dstrect.x += self.vel.x;
	self.tex.dstrect.y += self.vel.y;
}

void EnemySetDirectoin(Enemy& self, Ship& ship)
{
	VecSetDirectionByCoords(
		self.vel,
		{ self.tex.dstrect.x + self.tex.dstrect.w / 2, self.tex.dstrect.y + self.tex.dstrect.h / 2 },
		{ ship.tex.dstrect.x + ship.tex.dstrect.w / 2, ship.tex.dstrect.y + ship.tex.dstrect.h / 2 }
	);

	VecSetLen(self.vel, 5);

	VecSetLen(self.acc, 0.1);
	VecSetDirection(self.acc, -VecGetAngle(self.vel));
}

void EnemyIsCloseWithShip(Enemy& self, Ship& ship)
{

}

void EnemyUpdate(Enemy& self, Ship& ship)
{
	EnemyUpdateMovement(self);
	boundScreen(self.tex.dstrect);

	int ticks = SDL_GetTicks();
	if (ticks - self.ticks >= ENEMY_DELAY) self.ticks = ticks;
	else return;

	EnemySetDirectoin(self, ship);
}

void EnemyDraw(Enemy& self)
{
	SDL_RenderCopy(ren, self.tex.tex, 0, &self.tex.dstrect);
}
