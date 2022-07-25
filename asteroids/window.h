#pragma once
#include <SDL.h>

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int winWdt;
extern int winHgt;

void init();
void deInit(int error);

void boundWindow(SDL_Rect &rect);