#pragma once
#include <SDL.h>

#define max(a,b) (((a)>(b))?(a):(b))

bool isCircsColliding(SDL_Point p1, float r1, SDL_Point p2, float r2);
bool isPointInCirc(SDL_Point circ, float r, SDL_Point p);

void fillRect(SDL_Rect& rect, const SDL_Color& col);

SDL_Point getRectCenter(SDL_Rect& rect);
float getRadius(SDL_Rect& rect);

void centerizeRect(SDL_Rect& centerize, SDL_Rect& border);
