#include "texture.h"

Texture loadTexture(const char filename[])
{
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf)
    {
        printf("\nCouldn't load image! Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    Texture texture;
    texture.tex = SDL_CreateTextureFromSurface(ren, surf);
    texture.w = surf->w;
    texture.h = surf->h;
    texture.dstrect = { 0, 0, texture.w, texture.h };

    SDL_FreeSurface(surf);

    return texture;
}