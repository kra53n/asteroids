#include <math.h>
#include "constants.h"
#include "vector.h"

float VecGetLenSquared(Vec& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VecGetLen(Vec& vec)
{
	return sqrt(VecGetLenSquared(vec));
}

// Change direction of vector on angle in degrees
void VecChangeDirection(Vec& vec, float angle)
{
	angle *= RADIANS;
	angle += atan2(vec.y, vec.x);
	float len = VecGetLen(vec);
	vec.x = cos(angle) * len;
	vec.y = -sin(angle) * len;
}

// Set direction of vector in degrees
void VecSetDirection(Vec& vec, float angle)
{
	angle *= RADIANS;
	float len = VecGetLen(vec);
	vec.x = cos(angle) * len;
	vec.y = -sin(angle) * len;
}

void VecSumCoords(Vec& vec1, Vec& vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
}