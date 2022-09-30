#pragma once
#include <SDL.h>

#include "config.h"
#include "texture.h"

#define max(a,b) (((a)>(b))?(a):(b))

enum SORTING_BY { SORTING_BY_INCREMENCE, SORTING_BY_DECREMENCE };

void sortNums(int* nums, int size, int by = SORTING_BY_INCREMENCE);

bool isCircsColliding(SDL_Point p1, float r1, SDL_Point p2, float r2);
bool isPointInCirc(SDL_Point circ, float r, SDL_Point p);

void fillRect(SDL_Rect& rect, const SDL_Color& col);

SDL_Point getRectCenter(SDL_Rect& rect);
float getRadius(SDL_Rect& rect);

void centerizeRect(SDL_Rect& centerize, SDL_Rect& border);

void updateMaxValue(float& value, float maximum);

void drawBorderLine(int x1, int y1, int x2, int y2, int size, SDL_Color& col);
void drawBorderRect(SDL_Rect& rect, int size, SDL_Color& col);
