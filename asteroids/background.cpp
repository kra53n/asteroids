#include <stdio.h>

#include "vector.h"
#include "structs.h"
#include "background.h"

void BackgroundInit(Texture& texture, int index)
{
	if (index >= BACKGROUND_FILENAMES_NUM || index < 0)
	{
		printf("\nIndex error in BackgroundInit! Only [0;%d] possible, %d was put!\n", BACKGROUND_FILENAMES_NUM, index);
		system("pause");
		exit(1);
	}
	texture = loadTexture(FILENAMES[index]);
}

void BackgroundUpdate(Game& game)
{
	float speed = 0.5;
    game.background.dstrect.x += -game.ship.vel.x * speed;
    game.background.dstrect.y += -game.ship.vel.y * speed;

	if (!VecGetLen(game.ship.vel)) return;

    if (game.background.dstrect.x < -game.background.dstrect.w
        || game.background.dstrect.x > game.background.dstrect.w)
        game.background.dstrect.x = 0;
    if (game.background.dstrect.y < -game.background.dstrect.h
        || game.background.dstrect.y > game.background.dstrect.h)
        game.background.dstrect.y = 0;
}

void BackgroundDraw(Game& game)
{
    SDL_Rect rect;
    int wdt = 0;
    int hgt = 0;

    if (game.background.dstrect.x < 0)
        wdt = game.background.dstrect.w;
    else if (game.background.dstrect.x > 0)
        wdt = -game.background.dstrect.w;

    if (game.background.dstrect.y < 0)
        hgt = game.background.dstrect.h;
    else if (game.background.dstrect.y > 0)
        hgt = -game.background.dstrect.h;

    SDL_RenderCopy(ren, game.background.tex, NULL, &game.background.dstrect);
    if (wdt)
    {
        rect = game.background.dstrect;
        rect.x += wdt;
        SDL_RenderCopy(ren, game.background.tex, NULL, &rect);
    }
    if (hgt)
    {
        rect = game.background.dstrect;
        rect.y += hgt;
        SDL_RenderCopy(ren, game.background.tex, NULL, &rect);
    }
    if (wdt && hgt)
    {
        rect = game.background.dstrect;
        rect.x += wdt;
        rect.y += hgt;
        SDL_RenderCopy(ren, game.background.tex, NULL, &rect);
    }
}
