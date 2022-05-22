#include "window.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 1200;
int winHgt = 800;

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL couldn't init SDL_INIT_VIDEO! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    if (SDL_Init(IMG_INIT_PNG) < 0)
    {
        printf("SDL couldn't init IMG_INIT_PNG! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    if (TTF_Init())
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    win = SDL_CreateWindow("Asteroids!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    if (win == NULL)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        printf("SDL couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }
}

void deInit(int error)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}