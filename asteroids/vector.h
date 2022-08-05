#pragma once

struct Vec
{
	float x;
	float y;
};

float VecGetLenSquared(Vec& vec);
float VecGetLen(Vec& vec);

void VecChangeDirection(Vec& vec, float angle);
void VecSetDirection(Vec& vec, float angle);