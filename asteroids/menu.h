#pragma once
#include "config.h"
#include "texture.h"

struct Menu
{
    // textures of options
    Texture textures[MENU_OPTIONS_NUM];
    // choice of texture option
    int choice = 0;
    // text block position of top
    int textBlockY;
    int ticks;
};

void MenuInit(Menu& menu);
void MenuDestroy(Menu& menu);
void MenuUpdate(Menu& menu, Keys& keys, int& gameState);
void MenuDraw(Menu& menu);