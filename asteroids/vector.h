#pragma once

struct Vec
{
	float x;
	float y;
};

float VecGetLenSquared(Vec& vec);
float VecGetLen(Vec& vec);

void VecSetLen(Vec& vec, float len);
void VecChangeDirection(Vec& vec, float angle);
void VecSetDirection(Vec& vec, float angle);

void VecSumCoords(Vec& vec1, Vec& vec2);