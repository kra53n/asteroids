#include "window.h"

#pragma once

struct Texture
{
	SDL_Texture* tex = NULL;
    int w;
    int h;
	SDL_Rect dstrect;
};

Texture loadTexture(const char filename[]);
