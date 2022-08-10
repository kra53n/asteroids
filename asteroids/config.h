#pragma once
#include <SDL.h>

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
	"assets/images/stars/Nebula Red.png",
};

// PARTICLES CONFIGURATION

#define PARTICLES_FILENAMES_NUM 3

const char PARTICLES_FILENAMES[PARTICLES_FILENAMES_NUM][41] = {
	"assets/images/backgrounds/particles1.png",
	"assets/images/backgrounds/particles2.png",
	"assets/images/backgrounds/particles3.png",
};

// BULLET CONFIGURATION

const char BULLETS_FILENAMES[][40] = {
    "assets/images/bullets/bullet1.png",
};


// SHIP CONFIGURATION

const char SHIP_FILENAMES_TEXTURES[][40] = {
	"assets/images/ships/aurora.png",
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

const float ASTEROIDS_DENSITY[ASTEROIDS_TYPE_NUM] = {
    7.874      ,
    10.3  * 2  ,
    4.34  * 2  ,
    4.34  * 0.9,
    4.34       ,
    4.6        ,
    10.49      ,
    4.34  * 0.8,
    6.505      ,
};
