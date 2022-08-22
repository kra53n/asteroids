#pragma once
#include <SDL.h>

// MENU CONFIGURATION

#define         MENU_FONTNAME                 "assets/fonts/Voyager Heavy.otf"
#define         MENU_FONT_HGT                 50
#define         MENU_FONT_VERTICAL_DISTANCE   80
#define         MENU_OPTIONS_NUM              3
#define         MENU_DELAY_BUTTONS            200
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

#define BULLETS_TYPE_NUM 4

const char BULLETS_FILENAMES[][40] = {
    "assets/images/bullets/bullet1.png",
    "assets/images/bullets/bullet1.png",
    "assets/images/bullets/bullet2.png",
    "assets/images/bullets/bullet2.png",
};

const unsigned BULLETS_SPEED[] = {
	80,
	10,
	10,
	10,
};

const unsigned BULLETS_DELAY[] = {
	200,
	800,
	1000,
	1000,
};


// SHIP CONFIGURATION

#define ENGINE_FRAMES_NUM 4
#define SHIP_SCALE_COEFF  3

#define ENGINE_FILENAME      "assets/images/engine/engine_fire"
#define ENGINE_FILENAME_TYPE "png"
#define ENGINE_FRAMES         15
#define ENGINE_DELAY          100

const char SHIP_FILENAMES_TEXTURES[][40] = {
	"assets/images/ships/ship.png",
};


// ASTEROIDS CONFIGURATION

#define ASTEROIDS_TYPE_NUM      9
#define EXPLOSION_FILENAME      "assets/images/explosion/explosion"
#define EXPLOSION_FILENAME_TYPE "png"
#define EXPLOSION_FRAMES         9
#define EXPLOSION_DELAY          100
#define EXPLOSION_SCALE_COEFF    4

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
