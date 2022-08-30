#pragma once
#include <SDL.h>

bool isCircsColliding(SDL_Point p1, float r1, SDL_Point p2, float r2);
bool isPointInCirc(SDL_Point circ, float r, SDL_Point p);
