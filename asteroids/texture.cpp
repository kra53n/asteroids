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
    TTF_CloseFont(font);

    Texture texture;
    texture.tex = SDL_CreateTextureFromSurface(ren, surf);
    texture.w = surf->w;
    texture.h = surf->h;
    texture.dstrect = { 0, 0, texture.w, texture.h };

    SDL_FreeSurface(surf);

    return texture;
}