#include "menu.h"
#include "constants.h"
#include "window.h"
#include "texture.h"

void MenuInit(Menu& menu)
{
	for (int i = 0; i < menu.texturesNum; i++)
	{
		menu.textures[i] = loadFont(MENU_OPTIONS[i], MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_HGT);
	}
	menu.textBlockY = (winHgt - ((MENU_FONT_HGT + MENU_FONT_VERTICAL_DISTANCE) * menu.texturesNum - MENU_FONT_VERTICAL_DISTANCE)) / 2;
}

void MenuDestroy(Menu& menu)
{
	for (int i = 0; i < menu.texturesNum; i++)
	{
		SDL_DestroyTexture(menu.textures[i].tex);
	}
}

void MenuProcess(Menu& menu)
{

}

void MenuDraw(Menu& menu)
{
	SDL_Rect drawRect = { 0, menu.textBlockY, 0, 0};

	for (int i = 0; i < menu.texturesNum; i++)
	{
		drawRect.w = menu.textures[i].dstrect.w;
		drawRect.h = menu.textures[i].dstrect.h;
		drawRect.x = (winWdt - drawRect.w) / 2;
		SDL_RenderCopy(ren, menu.textures[i].tex, NULL, &drawRect);
		drawRect.y += drawRect.h + MENU_FONT_VERTICAL_DISTANCE;
	}
}