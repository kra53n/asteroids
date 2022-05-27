#pragma once
#include "window.h"

struct Texture
{
	SDL_Texture* tex      = NULL;
    int          w;
    int          h;
	SDL_Rect     dstrect;
	double       angle    = 0;
};

Texture loadTexture(const char filename[]);
Texture loadFont(const char text[], const char fontname[], SDL_Color color, int hgt);