#pragma once
#include "config.h"
#include "texture.h"

struct Menu
{
    const MENU_INFO* info;
    Texture*         textures = 0;
    // restart chosen mode
    bool             restart;
    int              num;
    int              choice   = 0;
    // text block position of top
    int              textBlockY;
    int              ticks;
};

void MenuInit(Menu& menu, const MENU_INFO* info, int optionsNum);
void MenuDestroy(Menu& menu);
void MenuUpdate(Menu& menu, Keys& keys, int& gameState);
void MenuDraw(Menu& menu);