#pragma once
#include <SDL.h>

#include "window.h"

struct Texture
{
    SDL_Texture* tex      = NULL;
    SDL_Rect     dstrect;
    double       angle    = 0;
};

Texture loadTexture(const char filename[]);
Texture loadFont(const char text[], const char fontname[], SDL_Color color, int hgt);

SDL_Point getRectCenter(SDL_Rect& rect);
float getRadius(SDL_Rect& rect);

void TextureUpdateAsInfiniteImage(Texture& self, SDL_FPoint offset, bool cond = true);
void TextureDrawAsInfiniteImage(Texture& self);
