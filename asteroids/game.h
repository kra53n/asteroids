#pragma once
#include <SDL_mixer.h>

#include "menu.h"
#include "ship.h"
#include "music.h"
#include "enemy.h"
#include "level.h"
#include "config.h"
#include "bullet.h"
#include "texture.h"
#include "asteroid.h"

struct Game
{
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
    
    Music      music;
};

void processKeys(Game& game);

void GameInit(Game& game);
void GameDraw(Game& game);
void GameUpdate(Game& game);
void GameLoop(Game& game);
