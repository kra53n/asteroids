#pragma once

#define ASTEROIDS_TYPE_NUM 9

struct Level {
	int  levelNumber;
	int  background;
	int  asters[ASTEROIDS_TYPE_NUM];
	bool enemy;
};

// NOTE: oh I shoult move it in Asteroids!
#define DEFAULT_LEVELS_NUM 7

const Level DEFAULT_LEVELS[DEFAULT_LEVELS_NUM] = {
	{ 1, 0, { 0, 0, 0, 0, 1, 0, 0, 0, 0 }, 0 },
	{ 2, 1, { 0, 0, 0, 1, 0, 1, 0, 0, 0 }, 0 },
	{ 3, 0, { 0, 0, 1, 0, 1, 0, 1, 0, 0 }, 0 },
	{ 4, 2, { 0, 1, 0, 0, 1, 0, 0, 1, 0 }, 0 },
	{ 5, 0, { 0, 0, 1, 0, 1, 0, 1, 0, 0 }, 1 },
	{ 6, 1, { 0, 0, 0, 1, 1, 1, 0, 0, 0 }, 1 },
	{ 7, 3, { 1, 1, 1, 0, 1, 0, 1, 1, 1 }, 1 },
};
