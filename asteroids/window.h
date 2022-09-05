#pragma once
#include <SDL.h>

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int winWdt;
extern int winHgt;
extern int winWdt2;
extern int winHgt2;
extern SDL_Rect winRect;

void init();
void deInit(int error);

void boundScreen(SDL_Rect &rect);