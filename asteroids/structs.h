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

struct Ship
{
    Texture tex;
    float   speedMovement = 10;
    float   speedRotation = 4;
    int     wdt           = 242;
};

struct Game {
    int        wdt = winWdt;
    int        hgt = winHgt;

    bool       run = false;
    int        state = 0;
    SDL_Event  event;
    KeysStatus keysStatus;

    Texture    background;
    Ship       ship;

    Menu       menu;
};