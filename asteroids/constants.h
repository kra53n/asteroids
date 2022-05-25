#pragma once
#include <SDL.h>

// MENU CONFIGURATION
const char MENU_FONTNAME[] = "assets/fonts/Voyager Heavy.otf";
const int MENU_FONT_HGT = 50;
const int MENU_OPTIONS_NUM = 3;
const int MENU_FONT_VERTICAL_DISTANCE = 80;
const char MENU_OPTIONS[][9] = { "start", "settings", "exit" };
const SDL_Color COLOR_OF_ACTIVE_OPTION = { 255, 0, 0, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION = { 150, 150, 220, 255 };
