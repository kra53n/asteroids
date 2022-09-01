#pragma once
#include <SDL.h>


// GAME CONFIGURATION

enum gameStates
{
    GAME_STATE_MENU,
    GAME_STATE_PLAY,
    GAME_STATE_SETTINGS,
    GAME_STATE_EXIT,

    GAME_STATE_RESTART,

    GAME_STATE_SOLO,
    GAME_STATE_SEAT,
};

struct Keys
{
    bool left     = false;
    bool right    = false;
    bool up       = false;
    bool down     = false;
    bool btnLeft  = false;
    bool space    = false;
    bool enter    = false;
    bool escape   = false;
    int  mouse_x;
    int  mouse_y;
};


// MENU CONFIGURATION

#define         MENU_FONTNAME                 "assets/fonts/Voyager Heavy.otf"
#define         MENU_FONT_SIZE                50
#define         MENU_FONT_VERTICAL_DISTANCE   80
#define         MENU_DELAY_BUTTONS            200

const SDL_Color COLOR_OF_ACTIVE_OPTION      = { 255, 0, 0, 255 };
const SDL_Color COLOR_OF_NON_ACTIVE_OPTION  = { 150, 150, 220, 255 };

struct MENU_INFO
{
    const char* name;
    int         mode;
};

#define MAIN_MENU_NUM 3

const MENU_INFO MAIN_MENU[MAIN_MENU_NUM] = {
    { "start",    GAME_STATE_PLAY     },
    { "settings", GAME_STATE_SETTINGS },
    { "exit",     GAME_STATE_EXIT     },
};


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
    unsigned damage;
};

#define BULLETS_TYPE_NUM 4

const BULLET_INFO BULLETS[BULLETS_TYPE_NUM] = {
    { "assets/images/bullets/bullet1.png", 80,  200,  1 },
    { "assets/images/bullets/bullet1.png", 100, 800,  2 },
    { "assets/images/bullets/bullet2.png", 10,  1000, 3 },
    { "assets/images/bullets/bullet2.png", 10,  1000, 4 },
};


// SHIP CONFIGURATION

#define ENGINE_FRAMES_NUM 4
#define SHIP_SCALE_COEFF  3

#define ENGINE_FILENAME      "assets/images/engine/engine_fire"
#define ENGINE_FILENAME_TYPE "png"
#define ENGINE_FRAMES         15
#define ENGINE_DELAY          100

#define SHIP_FILENAME "assets/images/ships/ship.png"


// ENEMY CONFIGURATION

#define ENEMY_FILENAME      "assets/images/enemy/enemy.png"
#define ENEMY_DAMAGE        0.25
#define ENEMY_BULLET_DAMAGE 5
#define ENEMY_HEALTH        200
#define EMEMY_MAX_SPEED     30
#define ENEMY_DELAY         100
#define ENEMY_SCALE_COEFF   4


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
    char     filename[40];
    float    mass;
    unsigned health;
    unsigned damage;
};

#define ASTEROIDS_TYPE_NUM 9

const ASTEROID_INFO ASTEROIDS[ASTEROIDS_TYPE_NUM] = {
    { "assets/images/asteroids/iron.png",        7.874,      10, 2 },
    { "assets/images/asteroids/large metal.png", 10.3 * 2,   10, 2 },
    { "assets/images/asteroids/large rock.png",  4.34 * 2,   10, 2 },
    { "assets/images/asteroids/medium rock.png", 4.34 * 0.9, 10, 2 },
    { "assets/images/asteroids/rock.png",        4.34,       10, 2 },
    { "assets/images/asteroids/silicon.png",     4.6,        10, 2 },
    { "assets/images/asteroids/silver.png",      10.49,      10, 2 },
    { "assets/images/asteroids/small rock.png",  4.34 * 0.8, 10, 2 },
    { "assets/images/asteroids/titanium.png",    6.505,      10, 2 },
};
