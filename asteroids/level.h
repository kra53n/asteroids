#pragma once
#include "config.h"

#define LevelState int

enum LEVEL_READING_STATE
{
	LEVEL_STATE,
	LEVEL_NEXT,

	LEVEL_NUM,
	LEVEL_BACKGROUND,
	LEVEL_ASTEROIDS,
	LEVEL_ENEMY,
};

struct Level
{
	int  num;
	int  bgNum;
	int  asters[ASTEROIDS_TYPE_NUM];
	bool enemy;
};

struct Levels
{
	Level* levels = 0;
	int num = 0;
};

Levels LevelLoadFile(const char* filename);
