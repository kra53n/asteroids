#pragma once
#include "config.h"
#include "texture.h"

#define LevelState int

enum LEVEL_READING_STATE
{
	LEVEL_STATE,
	LEVEL_NEXT,

	LEVEL_NUM,
	LEVEL_BACKGROUND,
	LEVEL_ASTEROIDS,
	LEVEL_ENEMY,
	LEVEL_RECORD,
};

enum SHIFTING_ELEMNTS
{
	LEVEL_SHIFT_UP,
	LEVEL_SHIFT_DOWN,
};

struct Level
{
	int          num;
	int          bgNum;
	int          asters[ASTEROIDS_TYPE_NUM];
	const char*  record;
	bool         enemy;
};

struct Levels
{
	Level*   levels   = 0;
	int      num      = 0;

	int      inited   = false;
	int      x;
	int      cur      = 0;
	int      ticks;
	Texture* textures;
};

Levels LevelLoadFile(const char* filename);

void LevelInit(Levels& levels);
void LevelDestroy(Levels& levels);
void LevelUpdate(Levels& levels, Keys& keys);
void LevelDraw(Levels& levels);
