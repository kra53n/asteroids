#include <math.h>
#include "config.h"
#include "vector.h"

float VecGetLenSquared(Vec& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VecGetLen(Vec& vec)
{
	return sqrt(VecGetLenSquared(vec));
}

float VecGetAngle(Vec& vec)
{
	float angle = atan2(-vec.y, vec.x);
	angle /= RADIANS;
	return angle;
}

void VecSetLen(Vec& vec, float len)
{
	float angle = atan2(vec.y, vec.x);
	vec.x = cos(angle) * len;
	vec.y = -sin(angle) * len;
}

// Change direction on angle in degrees
void VecChangeDirection(Vec& vec, float angle)
{
	angle *= RADIANS;
	angle += atan2(vec.y, vec.x);
	float len = VecGetLen(vec);
	vec.x = cos(angle) * len;
	vec.y = -sin(angle) * len;
}

// Set direction in degrees
void VecSetDirection(Vec& vec, float angle)
{
	angle *= RADIANS;
	float len = VecGetLen(vec);
	vec.x = cos(angle) * len;
	vec.y = -sin(angle) * len;
}

// Set direction from p1 to p2
void VecSetDirectionByCoords(Vec& vec, SDL_Point p1, SDL_Point p2)
{
	vec.x = p2.x - p1.x;
	vec.y = p1.y - p2.y;
}

void VecSetLenByCoords(Vec& vec, SDL_Point p1, SDL_Point p2)
{
	int x = p2.x - p1.x;
	int y = p2.y - p1.y;
	VecSetLen(vec, sqrt(x*x + y*y));
}

void VecSumCoords(Vec& vec1, Vec& vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
}