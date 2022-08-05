#include <SDL.h>
#include <math.h>

#include "ship.h"
#include "window.h"
#include "texture.h"
#include "structs.h"
#include "constants.h"

/* wdt - width of ship in the game */
void ShipInit(Ship& self, int wdt)
{
	self.lastTicks = SDL_GetTicks();
	self.tex = loadTexture(SHIP_FILENAMES_TEXTURES[0]);

	self.tex.dstrect.x = winWdt / 2;
	self.tex.dstrect.y = winHgt / 2;
	float coeff = self.tex.dstrect.w / self.wdt;
	self.tex.dstrect.w /= coeff;
	self.tex.dstrect.h /= coeff;
}

void ShipUpdateVelocity(Ship& self, KeysStatus& keys)
{
	if (fabs(self.vel.x) > self.maxSpeed)
		self.vel.x = self.vel.x > 0 ? self.maxSpeed : -self.maxSpeed;
	if (fabs(self.vel.y) > self.maxSpeed)
		self.vel.y = self.vel.y > 0 ? self.maxSpeed : -self.maxSpeed;

	self.tex.dstrect.x += self.vel.x;
	self.tex.dstrect.y -= self.vel.y;

	if (keys.up) return;

	int ticks = SDL_GetTicks();
	if (ticks - self.lastTicks >= 1000)
	{
		self.lastTicks = ticks;
		self.vel.x /= 1.8;
		self.vel.y /= 1.8;
	}
}

void ShipUpdatAcceleration(Ship& self, KeysStatus& keys)
{
	if (keys.up)
	{
		self.acc = { 1, 0 };
		VecSetDirection(self.acc, self.tex.angle);
		VecSumCoords(self.vel, self.acc);
	}
}

void ShipUpdate(Ship& self, KeysStatus& keys)
{
	ShipUpdateVelocity(self, keys);
	ShipUpdatAcceleration(self, keys);

	if (keys.left)
		self.tex.angle -= self.speedRotation;
	if (keys.right)
		self.tex.angle += self.speedRotation;

	boundScreen(self.tex.dstrect);
}

void ShipDraw(Ship& self)
{
	SDL_RenderCopyEx(ren, self.tex.tex, NULL, &self.tex.dstrect, self.tex.angle, NULL, SDL_FLIP_NONE);
}