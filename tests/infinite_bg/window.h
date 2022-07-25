#include <stdio.h>
#include <SDL.h>

int winWdt = 1280;
int winHgt = 720;

SDL_Window* win = SDL_CreateWindow("Infinite background", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN);
SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

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

    if (win == NULL)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    if (ren == NULL)
    {
        printf("SDL couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) == NULL)
    {
        printf("SDL_image couldn`t be initialized! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
        exit(1);
    }
}