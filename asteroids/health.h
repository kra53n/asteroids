#pragma once
#include <SDL.h>

struct Health
{
	unsigned point;
	SDL_Rect rect;
};

void HealthInit(Health& self, SDL_Rect rect, int point = 100);
void HealthUpdate(Health& self, int point = 0);
void HealthDraw(Health& self);
