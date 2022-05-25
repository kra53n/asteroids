#pragma once
#include <SDL.h>
#include "window.h"
#include "structs.h"
#include "menu.h"

struct Game {
    int wdt = winWdt;
    int hgt = winHgt;

    bool run = false;
    SDL_Event event;
    KeysStatus keysStatus;

    Texture background;

    Menu menu;
};

void processKeys(Game& game);

void GameInit(Game& game);
void GameDraw(Game& game);
void GameUpdate(Game& game);
void GameLoop(Game& game);
