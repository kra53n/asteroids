#pragma once
#include <SDL.h>

// MENU CONFIGURATION

#define         MENU_FONTNAME                 "assets/fonts/Voyager Heavy.otf"
#define         MENU_FONT_SIZE                50
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

struct BULLET_INFO
{
	char     filename[40];
	unsigned speed;
	unsigned delay;
};

#define BULLETS_TYPE_NUM 4

const BULLET_INFO BULLETS[BULLETS_TYPE_NUM] = {
	{ "assets/images/bullets/bullet1.png", 80, 200  },
	{ "assets/images/bullets/bullet1.png", 10, 800  },
	{ "assets/images/bullets/bullet2.png", 10, 1000 },
	{ "assets/images/bullets/bullet2.png", 10, 1000 },
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


// SCORE CONFIGURATION

#define SCORE_FONTNAME "assets/fonts/Voyager Heavy.otf"
#define SCORE_FONT_SIZE 35


// EXPLOSION CONFIGURATION

#define EXPLOSION_FILENAME      "assets/images/explosion/explosion"
#define EXPLOSION_FILENAME_TYPE "png"
#define EXPLOSION_FRAMES         9
#define EXPLOSION_DELAY          100
#define EXPLOSION_SCALE_COEFF    4


// ASTEROIDS CONFIGURATION

struct ASTEROID_INFO
{
	char  filename[40];
	float mass;
	float health;
};

#define ASTEROIDS_TYPE_NUM 9

const ASTEROID_INFO ASTEROIDS[ASTEROIDS_TYPE_NUM] = {
	{ "assets/images/asteroids/iron.png",        7.874,      100 },
	{ "assets/images/asteroids/large metal.png", 10.3 * 2,   100 },
	{ "assets/images/asteroids/large rock.png",  4.34 * 2,   100 },
	{ "assets/images/asteroids/medium rock.png", 4.34 * 0.9, 100 },
	{ "assets/images/asteroids/rock.png",        4.34,       100 },
	{ "assets/images/asteroids/silicon.png",     4.6,        100 },
	{ "assets/images/asteroids/silver.png",      10.49,      100 },
	{ "assets/images/asteroids/small rock.png",  4.34 * 0.8, 100 },
	{ "assets/images/asteroids/titanium.png",    6.505,      100 },
};
