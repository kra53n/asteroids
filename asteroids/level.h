#pragma once
#include "config.h"

struct Level
{
	int  levelNumber;
	int  background;
	int  asters[ASTEROIDS_TYPE_NUM];
	bool enemy;
};
