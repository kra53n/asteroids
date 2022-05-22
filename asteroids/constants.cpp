#include <SDL.h>
#include "constants.h"

// MENU CONFIGURAGTION
const char MENU_FONTNAME[] = "assets/fonts/Equinox Bold.otf";
const int MENU_FONT_HGT = 60;
const int MENU_FONT_VERTICAL_DISTANCE = 100;
const char MENU_OPTIONS[][9] = { "Start", "Settings", "Exit"};
const SDL_Color COLOR_OF_ACTIVE_OPTION = { 150, 150, 220, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION = { 255, 0, 0, 255 };
