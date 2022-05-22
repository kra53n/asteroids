#include "constants.h"
#include "texture.h"

#pragma once

struct Menu
{
	//bool isPlayed = false;

	int texturesNum = 3;
	Texture textures[3];
	int textBlockY;
};

void MenuInit(Menu& menu);
void MenuDestroy(Menu& menu);
void MenuProcess(Menu& menu);
void MenuDraw(Menu& menu);