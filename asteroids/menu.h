#pragma once
#include "structs.h"

void MenuInit(Menu& menu);
void MenuDestroy(Menu& menu);
void MenuUpdate(Menu& menu, Keys& keys, int& gameState);
void MenuDraw(Menu& menu);