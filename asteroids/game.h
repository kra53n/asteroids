#include <SDL.h>
#include "window.h"
#include "background.h"

#pragma once

struct KeysStatus
{
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

struct Game {
    int wdt;
    int hgt;
    bool run = false;
    SDL_Event event;

    Texture background;

    KeysStatus keysStatus;

    Texture textureFont;
};

void processKeys(Game& game);

void GameInit(Game& game);
void GameDraw(Game& game);
void GameUpdate(Game& game);
void GameLoop(Game& game);
