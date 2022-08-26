#pragma once
#include <SDL.h>

struct Health
{
	unsigned point;
	SDL_Rect rect;
};

void HealthInit(Health& self, SDL_Rect rect, unsigned point = 100);
void HealthUpdate(Health& self, unsigned point = 0);
void HealthDraw(Health& self);
