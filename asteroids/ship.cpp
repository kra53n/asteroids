#include <SDL.h>
#include <math.h>

#include "ship.h"
#include "funcs.h"
#include "vector.h"
#include "window.h"
#include "config.h"
#include "texture.h"
#include "structs.h"

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
}

void ShipUpdatAcceleration(Ship& self, KeysStatus& keys)
{
	if (keys.up)
	{
		self.acc = { 0.6, 0 };
		VecSetDirection(self.acc, self.tex.angle);
		VecSumCoords(self.vel, self.acc);
	}
}

void ShipUpdateTicks(Ship& self, KeysStatus& keys)
{
	int ticks = SDL_GetTicks();
	if (ticks - self.lastTicks >= 1000)
	{
		self.lastTicks = ticks;

		if (keys.up)
		{
			int sign = self.rotationPower > 0 ? -1 : 1;
			self.rotationPower += sign * self.rotationCoeff;
		}
		else
		{
			self.vel.x /= 1.8;
			self.vel.y /= 1.8;
		}
	}
}

void ShipUpdateCollisionWithAstroids(Ship& self, Asteroids& asters)
{
	int shipR = self.tex.dstrect.w > self.tex.dstrect.h ? self.tex.dstrect.h : self.tex.dstrect.w;
	shipR /= 2;
	SDL_Point shipPoint = {
		self.tex.dstrect.x + self.tex.dstrect.w/2 ,
		self.tex.dstrect.y + self.tex.dstrect.h/2 
	};

	for (int i = 0; i < asters.num; i++)
	{
		int asterType = asters.asteroids[i].asteroidType;
		int asterR = asters.texture[asterType].dstrect.h / 2;
		SDL_Point asterPoint = {
			asters.asteroids[i].pos.x + asterR,
			asters.asteroids[i].pos.y + asterR
		};

		if (!isCircsColliding(shipPoint, shipR, asterPoint, asterR)) continue;
		
		VecSetDirectionByCoords(self.vel, asterPoint, shipPoint);
		VecSetDirectionByCoords(asters.asteroids[i].vel, shipPoint, asterPoint);

		float asterRebound = 60 / ASTEROIDS_DENSITY[asterType];
		float shipRebound = 70 / asterRebound;
		asterRebound /= shipR / 10;
		asterRebound *= shipR / 10;

		VecSetLen(self.vel, 70 / asterRebound);
		VecSetLen(asters.asteroids[i].vel, asterRebound);
	}
}

void ShipUpdate(Ship& self, Asteroids& asters, KeysStatus& keys)
{
    int sign = 0;
    if (keys.left)  sign = -1;
    if (keys.right) sign = 1;
	self.tex.angle += self.rotationPower;

    if (keys.up && sign)
    {
		self.tex.angle += sign * self.rotationSpeed;
        self.rotationPower = sign * 1.4;
    }

	ShipUpdateVelocity(self, keys);
	ShipUpdatAcceleration(self, keys);
    ShipUpdateTicks(self, keys);
	ShipUpdateCollisionWithAstroids(self, asters);

	boundScreen(self.tex.dstrect);
}

void ShipDraw(Ship& self)
{
	SDL_RenderCopyEx(ren, self.tex.tex, NULL, &self.tex.dstrect, self.tex.angle, NULL, SDL_FLIP_NONE);

     // int side = self.tex.dstrect.w > self.tex.dstrect.h ? self.tex.dstrect.h : self.tex.dstrect.w;
     // Vec line = { side / 2, 0 };
     // int x1 = self.tex.dstrect.x + side / 2;
     // int y1 = self.tex.dstrect.y + side / 2;

     // SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
     // for (int i = 0; i < 360; i += 15)
     // {
     //     VecSetDirection(line, i);
     //     int x2 = x1 + line.x;
     //     int y2 = y1 + line.y;
     //     SDL_RenderDrawLine(ren, x1, y1, x2, y2);
     // }
     // SDL_RenderDrawRect(ren, &self.tex.dstrect);
}
