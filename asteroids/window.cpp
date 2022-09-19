#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "window.h"

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 1280;
int winHgt = 720;
int winWdt2 = winWdt / 2;
int winHgt2 = winHgt / 2;
SDL_Rect winRect = { 0, 0, winWdt, winHgt };

void logError(const char* message, const char* error)
{
    printf("%s! SDL_Error: %s\n", message, error);
    system("pause");
    deInit(1);
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        logError("SDL couldn't initialize");

    if (SDL_Init(IMG_INIT_PNG) < 0)
        logError("SDL couldn't init IMG_INIT_PNG");

    if (TTF_Init())
        logError("SDL_TTF couldn't init TTF_Init");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024 * 26))
        logError("SDL_Mixer couldn't initialize", Mix_GetError());

    win = SDL_CreateWindow("Asteroids!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    if (win == NULL)
        logError("SDL couldn't init!");

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
        logError("SDL couldn't create renderer");
}

void deInit(int error)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}

void boundScreen(SDL_Rect &rect)
{
    int maxSide = rect.w >= rect.h ? rect.w : rect.h;

    bool right = rect.x >= winWdt;
    bool left = rect.x + maxSide <= 0;
    bool bottom = rect.y >= winHgt;
    bool top = rect.y + maxSide <= 0;

    if (right) rect.x = -maxSide;
    else if (left) rect.x = winWdt;
    else if (bottom) rect.y = -maxSide;
    else if (top) rect.y = winHgt;
}