#pragma once
#include <SDL.h>

#define RADIANS M_PI / 180

struct Vec
{
	float x;
	float y;
};

float VecGetLenSquared(Vec& vec);
float VecGetLen(Vec& vec);
float VecGetAngle(Vec& vec);

void VecSetLen(Vec& vec, float len);
void VecChangeDirection(Vec& vec, float angle);
void VecSetDirection(Vec& vec, float angle);
void VecSetDirectionByCoords(Vec& vec, SDL_Point p1, SDL_Point p2);
void VecSetLenByCoords(Vec& vec, SDL_Point p1, SDL_Point p2);

void VecSumCoords(Vec& vec1, Vec& vec2);
