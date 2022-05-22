#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "window.h"

SDL_Window* win;
SDL_Renderer* ren = NULL;

int winWdt = 1280;
int winHgt = 720;

void deInit(int error)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        printf("SDL couldn't SDL_Image! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    win = SDL_CreateWindow(u8"Треним", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    if (win == NULL)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        printf("SDL couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }
}