#pragma once
#include "texture.h"
#include "constants.h"
#include "structs.h"

struct Menu
{
	// textures of options
	Texture textures[MENU_OPTIONS_NUM];
	// choice of texture option
	int choice = 0;
	// text block position of top
	int textBlockY;
	int lastKeyTick;
};

void MenuInit(Menu& menu);
void MenuDestroy(Menu& menu);
void MenuProcess(Menu& menu, KeysStatus& keysStatus);
void MenuDraw(Menu& menu);