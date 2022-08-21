#include <SDL.h>
#include <math.h>
#include <stdio.h>

#include "ship.h"
#include "funcs.h"
#include "vector.h"
#include "window.h"
#include "config.h"
#include "texture.h"
#include "structs.h"

void EngineInit(Engine& self)
{
	char filename[200];
	for (int i = 0; i < ENGINE_FRAMES; i++)
	{
		sprintf_s(filename, 200, "%s%d.%s", ENGINE_FILENAME, i + 1, ENGINE_FILENAME_TYPE);
		self.texture[i] = loadTexture(filename);
		self.texture[i].dstrect.w *= SHIP_SCALE_COEFF;
		self.texture[i].dstrect.h *= SHIP_SCALE_COEFF;
	}

	self.ticks = SDL_GetTicks();
	self.frame = 0;
}

void EngineUpdate(Engine& self, KeysStatus& keys)
{
	int ticks = SDL_GetTicks();
	if (!(ticks - self.ticks >= ENGINE_DELAY)) return;

	self.frame = self.frame < ENGINE_FRAMES - 1 ? ++self.frame : 0;
}

void EngineDraw(Engine& self, Ship& ship, bool cond)
{
	if (!cond) return;

	Vec pos;
	VecSetLen(pos, (ship.tex.dstrect.w + self.texture->dstrect.w) / 2);
	VecSetDirection(pos, -ship.tex.angle);

	SDL_Rect dstrect = self.texture->dstrect;
	dstrect.x = ship.tex.dstrect.x + (ship.tex.dstrect.w - self.texture->dstrect.w) / 2 - pos.x;
	dstrect.y = ship.tex.dstrect.y + (ship.tex.dstrect.h - self.texture->dstrect.h) / 2 - pos.y;

	SDL_RenderCopyEx(ren, self.texture[self.frame].tex, 0, &dstrect, ship.tex.angle, 0, SDL_FLIP_NONE);
}

void ShipInit(Ship& self)
{
	self.ticks = SDL_GetTicks();
	self.tex = loadTexture(SHIP_FILENAMES_TEXTURES[0]);

	self.tex.dstrect.w *= SHIP_SCALE_COEFF;
	self.tex.dstrect.h *= SHIP_SCALE_COEFF;

	self.tex.dstrect.x = (winWdt - self.tex.dstrect.w) / 2;
	self.tex.dstrect.y = (winHgt - self.tex.dstrect.h) / 2;

	EngineInit(self.engine);
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
	if (ticks - self.ticks >= 1000)
	{
		self.ticks = ticks;

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

	for (Asteroid* aster = asters.head; aster != NULL; aster = aster->next)
	{
		int asterR = asters.texture[aster->type].dstrect.h / 2;
		SDL_Point asterPoint = {
			aster->pos.x + asterR,
			aster->pos.y + asterR
		};

		if (!isCircsColliding(shipPoint, shipR, asterPoint, asterR)) continue;
		
		VecSetDirectionByCoords(self.vel, asterPoint, shipPoint);
		VecSetDirectionByCoords(aster->vel, shipPoint, asterPoint);

		float asterRebound = 60 / ASTEROIDS_DENSITY[aster->type];
		float shipRebound = 70 / asterRebound;
		asterRebound /= shipR / 10;
		asterRebound *= shipR / 10;

		VecSetLen(self.vel, 70 / asterRebound);
		VecSetLen(aster->vel, asterRebound);
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
	
	EngineUpdate(self.engine, keys);

	boundScreen(self.tex.dstrect);
}

void ShipDraw(Ship& self, KeysStatus& keys)
{
	SDL_RenderCopyEx(ren, self.tex.tex, NULL, &self.tex.dstrect, self.tex.angle, NULL, SDL_FLIP_NONE);
	EngineDraw(self.engine, self, keys.up);

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
