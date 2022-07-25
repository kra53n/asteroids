#pragma once
#include <SDL.h>

#define RADIANS 180 * M_PI


// MENU CONFIGURATION
#define         MENU_FONTNAME                 "assets/fonts/Voyager Heavy.otf"
#define         MENU_FONT_HGT                 50
#define         MENU_FONT_VERTICAL_DISTANCE   80
#define         MENU_OPTIONS_NUM              3
const char      MENU_OPTIONS[][9]           = { "start", "settings", "exit" };
const SDL_Color COLOR_OF_ACTIVE_OPTION      = { 255, 0, 0, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION  = { 150, 150, 220, 255 };


// BACKGROUND CONFIGURATION
#define BACKGROUND_FILENAMES_NUM 4
#define BACKOGRUND_MOVE_SPEED    6

const char FILENAMES[BACKGROUND_FILENAMES_NUM][41] = {
	"assets/images/backgrounds/background.png",
	"assets/images/stars/Nebula Aqua-Pink.png",
	"assets/images/stars/Nebula Blue.png",
	"assets/images/stars/Nebula Red.png"
};


// SHIP CONFIGURATION
const char SHIP_FILENAMES_TEXTURES[][40] = {
	"assets/images/ships/megatrox.png",
};


// ASTEROIDS CONFIGURATION
#define ASTEROIDS_TYPE_NUM      9
#define ASTEROIDS_FILENAME      "assets/images/asteroids/iron.png"
const char ASTEROIDS_FILENAMES[ASTEROIDS_TYPE_NUM][40] = {
	"assets/images/asteroids/iron.png",
	"assets/images/asteroids/large metal.png",
	"assets/images/asteroids/large rock.png",
	"assets/images/asteroids/medium rock.png",
	"assets/images/asteroids/rock.png",
	"assets/images/asteroids/silicon.png",
	"assets/images/asteroids/silver.png",
	"assets/images/asteroids/small rock.png",
	"assets/images/asteroids/titanium.png",
};