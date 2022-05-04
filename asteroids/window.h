#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#pragma once

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int winWdt;
extern int winHgt;

void deInit(int error);
void init();