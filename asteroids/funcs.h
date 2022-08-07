#pragma once
#include <SDL.h>

bool isPointInRect(const SDL_Rect& rect, SDL_Point& point);
bool isCircsColliding(SDL_Point p1, float r1, SDL_Point p2, float r2);
