#pragma once
#include "menu.h"
#include "ship.h"
#include "enemy.h"
#include "level.h"
#include "config.h"
#include "bullet.h"
#include "texture.h"
#include "asteroid.h"

struct Game
{
    int        wdt         = winWdt;
    int        hgt         = winHgt;
                          
    bool       run         = false;
    bool       aboutInited = false;
    int        state       = 0;
    SDL_Event  event;
    Keys       keys;

    Menu       menu;
    Levels     levels;
    Texture    messageTexture;

    Texture    background;
    Texture    particles[PARTICLES_FILENAMES_NUM];
    Asteroids  asteroids;
    Ship       ship1;
    Ship       ship2;
    Enemy      enemy;
};

void processKeys(Game& game);

void GameInit(Game& game);
void GameDraw(Game& game);
void GameUpdate(Game& game);
void GameLoop(Game& game);
