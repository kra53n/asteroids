#include <SDL.h>
#include <stdio.h>

#include "game.h"
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
		SDL_Color color = i == menu.choice ? COLOR_OF_ACTIVE_OPTION : COLOR_OF_NON_ACTIVE_OPTION;
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, color, MENU_FONT_SIZE);
	}
}

void MenuInit(Menu& menu)
{
	menu.ticks = SDL_GetTicks();

	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_SIZE);
	}

	menu.textBlockY = (winHgt - ((MENU_FONT_SIZE + MENU_FONT_VERTICAL_DISTANCE) * MENU_OPTIONS_NUM - MENU_FONT_VERTICAL_DISTANCE)) / 2;
	changeTextureOptionColor(menu);
}

void MenuDestroy(Menu& menu)
{
	for (int i = 0; i < MENU_OPTIONS_NUM; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);
	}
}

void MenuChooseOptionByMouse(Menu& self, Keys& keys, bool& cursorUnderTexture)
{
	for (int opt = 0; opt < MENU_OPTIONS_NUM; opt++)
	{
		SDL_Point point = { keys.mouse_x, keys.mouse_y };
		cursorUnderTexture = SDL_PointInRect(&point, &self.textures[opt].dstrect);
		if (cursorUnderTexture)
		{
			self.choice = opt;
			changeTextureOptionColor(self);
			break;
		}
	}
}

void MenuChooseOptionByKbd(Menu& self, Keys& keys, int& ticks)
{
	if ((keys.up || keys.down) && ticks - self.ticks >= MENU_DELAY_BUTTONS)
	{
		self.ticks = ticks;
		if (keys.up)
		{
			self.choice = self.choice ? self.choice - 1 : MENU_OPTIONS_NUM - 1;
		}
		if (keys.down)
		{
			self.choice = (self.choice + 1) % MENU_OPTIONS_NUM;
		}
		changeTextureOptionColor(self);
	}
}

void MenuChangeOption(Menu& self, Keys& keys, int& gameState, int& ticks, bool& cursorUnderTexture)
{
	bool oneOfBtns = keys.enter || keys.space || (keys.btnLeft && cursorUnderTexture);
	if (oneOfBtns && ticks - self.ticks >= MENU_DELAY_BUTTONS)
	{
		self.ticks = ticks;
		gameState = self.choice + 1;
	}
}

void MenuUpdate(Menu& self, Keys& keys, int& gameState)
{
	int ticks = SDL_GetTicks();
	bool cursorUnderTexture = false;

	MenuChooseOptionByMouse(self, keys, cursorUnderTexture);
	if (!cursorUnderTexture)
		MenuChooseOptionByKbd(self, keys, ticks);
	
	MenuChangeOption(self, keys, gameState, ticks, cursorUnderTexture);
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
