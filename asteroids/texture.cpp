#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

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
    texture.dstrect = { 0, 0, surf->w, surf->h };
    texture.w = surf->w;
    texture.h = surf->h;

    SDL_FreeSurface(surf);

    return texture;
}

Texture loadFont(const char text[], const char fontname[], SDL_Color color, int hgt)
{
    TTF_Font* font = TTF_OpenFont(fontname, hgt);
    if (!font)
    {
        printf("\nCouldn't load font %s! Error: %s\n", fontname, SDL_GetError());
        system("pause");
        deInit(1);
    }

    SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
    if (!surf)
    {
        printf("\nCouldn't load surface from TTF_RenderText_Blended! Error: %s\n", SDL_GetError());
        system("pause");
        deInit(1);
    }

    Texture texture;
    texture.tex = SDL_CreateTextureFromSurface(ren, surf);
    texture.dstrect = { 0, 0, surf->w, surf->h };

    TTF_CloseFont(font);
    SDL_FreeSurface(surf);

    return texture;
}