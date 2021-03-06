#pragma once
#include "texture.h"
#include "constants.h"

enum gameStates
{
    GAME_STATE_MENU     = 0,
    GAME_STATE_PLAY     = 1,
    GAME_STATE_SETTINGS = 2,
    GAME_STATE_EXIT     = 3,
};

struct KeysStatus
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

struct Menu
{
    // textures of options
    Texture textures[MENU_OPTIONS_NUM];
    // choice of texture option
    int choice = 0;
    // text block position of top
    int textBlockY;
    int lastKeyTick;
};

struct Asteroid
{
    SDL_Point pos;
    SDL_Rect  srcrect;
    SDL_Rect  dstrect;
    int       frame     = 0;
    int       lastTicks;
};

struct Asteroids
{
    Texture   texture[ASTEROIDS_TYPE_NUM];
    int       asteroidsFrames[ASTEROIDS_TYPE_NUM];
    Asteroid* asteroids[ASTEROIDS_TYPE_NUM];
    int       num[ASTEROIDS_TYPE_NUM];
};

struct Ship
{
    Texture tex;
    float   speedMovement = 10;
    float   speedRotation = 4;
    int     wdt           = 242;
};

struct Game {
    int        wdt        = winWdt;
    int        hgt        = winHgt;
                          
    bool       run        = false;
    int        state      = 0;
    SDL_Event  event;
    KeysStatus keysStatus;

    Texture    background;
    Asteroids  asteroids;
    Ship       ship;

    Menu       menu;
};