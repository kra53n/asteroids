#include <SDL.h>

#include "game.h"
#include "menu.h"
#include "constants.h"
#include "window.h"
#include "texture.h"

void MenuInit(Menu& menu)
{
	menu.lastKeyTick = SDL_GetTicks();

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, menu.choice == i ? COLOR_OF_NON_ACTIVE_OPTION : COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
	}
	menu.textBlockY = (winHgt - ((MENU_FONT_HGT + MENU_FONT_VERTICAL_DISTANCE) * MENU_OPTIONS_NUM - MENU_FONT_VERTICAL_DISTANCE)) / 2;
}

void MenuDestroy(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);
	}
}

void MenuProcess(Menu& menu, KeysStatus& keysStatus)
{
	int tick = SDL_GetTicks();
	if (tick - menu.lastKeyTick >= 100)
	{
		menu.lastKeyTick = tick;
		if (keysStatus.up)
		{
			menu.textures[menu.choice] = loadFont(MENU_OPTIONS[menu.choice], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
			menu.choice = menu.choice ? menu.choice - 1 : MENU_OPTIONS_NUM - 1;
			menu.textures[menu.choice] = loadFont(MENU_OPTIONS[menu.choice], MENU_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION, MENU_FONT_HGT);
		}
		if (keysStatus.down)
		{
			menu.textures[menu.choice] = loadFont(MENU_OPTIONS[menu.choice], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
			menu.choice = (menu.choice + 1) % MENU_OPTIONS_NUM;
			menu.textures[menu.choice] = loadFont(MENU_OPTIONS[menu.choice], MENU_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION, MENU_FONT_HGT);
		}
	}

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		if ((menu.textures[i].dstrect.x <= keysStatus.mouse_x && keysStatus.mouse_x <= menu.textures[i].dstrect.x + menu.textures[i].dstrect.w) &&
			(menu.textures[i].dstrect.y <= keysStatus.mouse_y && keysStatus.mouse_y <= menu.textures[i].dstrect.y + menu.textures[i].dstrect.h))
		{
			menu.choice = i;
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