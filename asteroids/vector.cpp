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

void VecSetLen(Vec& vec, float len)
{
    float angle = atan2(vec.y, vec.x);
    vec.x = cos(angle) * len;
    vec.y = sin(angle) * len;
}

void VecSetLenByCoords(Vec& vec, SDL_Point p1, SDL_Point p2)
{
    Vec other = { p2.x - p1.x, p2.y - p1.y };
    VecSetLen(vec, VecGetLen(other));
}

float VecGetAngle(Vec& vec)
{
    float angle = atan2(vec.y, vec.x);
    angle /= RADIANS;
    return angle;
}

// Change direction on angle in degrees
void VecChangeAngle(Vec& vec, float angle)
{
    angle *= RADIANS;
    angle += atan2(vec.y, vec.x);
    float len = VecGetLen(vec);
    vec.x = cos(angle) * len;
    vec.y = sin(angle) * len;
}

// Set direction in degrees
void VecSetAngle(Vec& vec, float angle)
{
    angle *= RADIANS;
    float len = VecGetLen(vec);
    vec.x = cos(angle) * len;
    vec.y = sin(angle) * len;
}

// Set direction from p1 to p2
void VecSetAngleByCoords(Vec& vec, SDL_Point p1, SDL_Point p2)
{
    int x = p2.x - p1.x;
    int y = p2.y - p1.y;
    float angle = atan2(y, x);
    angle /= RADIANS;
    VecSetAngle(vec, angle);
}

void VecSumCoords(Vec& vec1, Vec& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
}

Vec& VecGetMaxVec(Vec& vec1, Vec& vec2)
{
    return VecGetLen(vec1) > VecGetLen(vec2) ? vec1 : vec2;
}