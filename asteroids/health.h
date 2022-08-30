#pragma once
#include <SDL.h>

struct Health
{
	float    point;
	SDL_Rect rect;
};

void HealthInit(Health& self, SDL_Rect rect = { 0, 0, 0, 0 }, float point = 100);
void HealthUpdate(Health& self, float point = 0);
void HealthDraw(Health& self);
