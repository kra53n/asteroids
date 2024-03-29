#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "window.h"
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

    SDL_Surface* surf = TTF_RenderUTF8_Blended_Wrapped(font, text, color, winWdt2);
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

// cond - condition for update
void TextureUpdateAsInfiniteImage(Texture& self, SDL_FPoint offset, bool cond)
{
    if (!cond) return;

    self.dstrect.x += offset.x;
    self.dstrect.y += offset.y;

    if (self.dstrect.x < -self.dstrect.w
        || self.dstrect.x > self.dstrect.w)
        self.dstrect.x = 0;
    if (self.dstrect.y < -self.dstrect.h
        || self.dstrect.y > self.dstrect.h)
        self.dstrect.y = 0;
}

void drawTextureWithOffset(Texture& texture, SDL_Point offset = { 0, 0 })
{
    SDL_Rect rect = texture.dstrect;
    rect.x += offset.x;
    rect.y += offset.y;
    SDL_RenderCopy(ren, texture.tex, 0, &rect);
}

void TextureDrawAsInfiniteImage(Texture& self)
{
    int wdt = 0;
    int hgt = 0;

    if (self.dstrect.x < 0)
        wdt = self.dstrect.w;
    else if (self.dstrect.x > 0)
        wdt = -self.dstrect.w;

    if (self.dstrect.y < 0)
        hgt = self.dstrect.h;
    else if (self.dstrect.y > 0)
        hgt = -self.dstrect.h;

    drawTextureWithOffset(self);
    if (wdt)
        drawTextureWithOffset(self, { wdt, 0 });
    if (hgt)
        drawTextureWithOffset(self, { 0, hgt });
    if (wdt && hgt)
        drawTextureWithOffset(self, { wdt, hgt });
}