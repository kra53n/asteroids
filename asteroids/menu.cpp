#include <SDL.h>

#include "menu.h"
#include "funcs.h"
#include "window.h"
#include "config.h"
#include "texture.h"

void changeTextureOptionColor(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);

		if (i == menu.choice)
		{
			menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
		}
		else
		{
			menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION, MENU_FONT_HGT);
		}
	}
}

void MenuInit(Menu& menu)
{
	menu.ticks = SDL_GetTicks();

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
	}
	menu.textBlockY = (winHgt - ((MENU_FONT_HGT + MENU_FONT_VERTICAL_DISTANCE) * MENU_OPTIONS_NUM - MENU_FONT_VERTICAL_DISTANCE)) / 2;
	changeTextureOptionColor(menu);
}

void MenuDestroy(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);
	}
}

void MenuProcess(Game& game)
{
	int ticks = SDL_GetTicks();

	// change choice for keyboard buttons
	if ((game.keysStatus.up || game.keysStatus.down) && ticks - game.menu.ticks >= MENU_DELAY_BUTTONS)
	{
		game.menu.ticks = ticks;
		if (game.keysStatus.up)
		{
			game.menu.choice = game.menu.choice ? game.menu.choice - 1 : MENU_OPTIONS_NUM - 1;
		}
		if (game.keysStatus.down)
		{
			game.menu.choice = (game.menu.choice + 1) % MENU_OPTIONS_NUM;
		}
		changeTextureOptionColor(game.menu);
	}

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		// change choice for option under mouse
		SDL_Point point = { game.keysStatus.mouse_x, game.keysStatus.mouse_y };
		bool cursorUnderTexture = isPointInRect(game.menu.textures[i].dstrect, point);
		if (cursorUnderTexture)
		{
			game.menu.choice = i;
			changeTextureOptionColor(game.menu);
		}
		
		bool oneOfBtns = game.keysStatus.enter || game.keysStatus.space || (game.keysStatus.btnLeft && cursorUnderTexture);
		if (oneOfBtns && ticks - game.menu.ticks >= MENU_DELAY_BUTTONS)
		{
			game.menu.ticks = ticks;
			game.state = game.menu.choice + 1;
		}
	}
}

void MenuDraw(Menu& menu)
{
	SDL_Rect drawRect = { 0, menu.textBlockY, 0, 0};

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		drawRect.w = menu.textures[i].dstrect.w;
		drawRect.h = menu.textures[i].dstrect.h;
		drawRect.x = (winWdt - drawRect.w) / 2;
		menu.textures[i].dstrect = drawRect;
		SDL_RenderCopy(ren, menu.textures[i].tex, NULL, &drawRect);
		drawRect.y += drawRect.h + MENU_FONT_VERTICAL_DISTANCE;
	}
}