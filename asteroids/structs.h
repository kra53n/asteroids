#pragma once
#include "vector.h"
#include "config.h"
#include "texture.h"

enum gameStates
{
    GAME_STATE_MENU     = 0,
    GAME_STATE_PLAY     = 1,
    GAME_STATE_SETTINGS = 2,
    GAME_STATE_EXIT     = 3,
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

struct Menu
{
    // textures of options
    Texture textures[MENU_OPTIONS_NUM];
    // choice of texture option
    int choice = 0;
    // text block position of top
    int textBlockY;
    int ticks;
};

struct Asteroid
{
    SDL_Point pos;
    SDL_Rect  srcrect;
    SDL_Rect  dstrect;
    Vec       vel;
    int       type;
    int       frame;
    int       ticks;
    Asteroid* next;
    Asteroid* prev;
};

struct Animation
{
    Texture* textures;
    int      frame;
    int      ticks;
};

struct Asteroids
{
    Animation explosion;
    Texture   texture[ASTEROIDS_TYPE_NUM];
    int       frames[ASTEROIDS_TYPE_NUM];
    Asteroid* head                        = 0;
};

struct Bullet
{
    Vec       vel;
    SDL_Point pos;
    unsigned  type;
    unsigned  ticks;
    Bullet*   next;
    Bullet*   prev;
};

struct Bullets
{
    Bullet*  head                    = 0;
    Texture  texs[BULLETS_TYPE_NUM];
    unsigned ticks                   = 0;
};

struct Ship
{
    Animation engine;
    Texture   tex;
    float     speedMovement = 0.5;
    float     rotationSpeed = 2.7;
    float     rotationCoeff = 0.1;
    int       rotationPower = 0;
    int       wdt           = 121;
    int       ticks         = 0;
    int       maxSpeed      = 10;
    Vec       vel           = { 0, 0 };
    Vec       acc           = { 0, 0 };
};

struct Game {
    int        wdt        = winWdt;
    int        hgt        = winHgt;
                          
    bool       run        = false;
    int        state      = 0;
    SDL_Event  event;
    Keys       keys;

    Texture    background;
    Texture    particles[PARTICLES_FILENAMES_NUM];
    Asteroids  asteroids;
    Ship       ship;
    Bullets    bullets;

    Menu       menu;
};
