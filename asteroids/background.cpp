#include <stdio.h>

#include "vector.h"
#include "structs.h"
#include "background.h"

void BackgroundInit(Texture& self, int index)
{
	if (index >= BACKGROUND_FILENAMES_NUM || index < 0)
	{
		printf("\nIndex error in BackgroundInit! Only [0;%d] possible, %d was put!\n", BACKGROUND_FILENAMES_NUM, index);
		system("pause");
		exit(1);
	}
	self = loadTexture(FILENAMES[index]);
}

void BackgroundUpdate(Texture& self, Ship& ship)
{
	float speed = 0.5;
    self.dstrect.x += -ship.vel.x * speed;
    self.dstrect.y += -ship.vel.y * speed;

	if (!VecGetLen(ship.vel)) return;

    if (self.dstrect.x < -self.dstrect.w
        || self.dstrect.x > self.dstrect.w)
        self.dstrect.x = 0;
    if (self.dstrect.y < -self.dstrect.h
        || self.dstrect.y > self.dstrect.h)
        self.dstrect.y = 0;
}

void BackgroundDraw(Texture& self)
{
    SDL_Rect rect;
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

    SDL_RenderCopy(ren, self.tex, NULL, &self.dstrect);
    if (wdt)
    {
        rect = self.dstrect;
        rect.x += wdt;
        SDL_RenderCopy(ren, self.tex, NULL, &rect);
    }
    if (hgt)
    {
        rect = self.dstrect;
        rect.y += hgt;
        SDL_RenderCopy(ren, self.tex, NULL, &rect);
    }
    if (wdt && hgt)
    {
        rect = self.dstrect;
        rect.x += wdt;
        rect.y += hgt;
        SDL_RenderCopy(ren, self.tex, NULL, &rect);
    }
}
