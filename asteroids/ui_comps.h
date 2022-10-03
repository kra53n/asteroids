#pragma once
#include <SDL.h>

#include "texture.h"

enum UI_TYPES { UI_TEXT, UI_BUTTON, UI_CHECKBUTTON, UI_SCALE };

enum UI_SCALE_MOVES { UI_SCALE_LEFT, UI_SCALE_RIGHT };

struct UI_Component
{
	int         type;

	// UI_TEXT, UI_BUTTON, UI_CHECKBUTTON, UI_SCALE
	const char* text;
	Texture     textTexture;
	int         hgt;
	SDL_Color   actCol;
	SDL_Color   nactCol;

	bool        act      = false;

	// keys
	bool        selected = false;
	bool        left     = false;
	bool        right    = false;
	int         ticks;

	// right margin from textTexture.x
	// if margin = 0, margin will be equal textTexture.x + textTexture.w
	int         margin   = 0;

	// UI_SCALE
	SDL_Rect    rect;
	int         maxScale;
	int         minScale;
	int         curScale;
};

UI_Component* UI_GetComponent(int type, const char* text, SDL_Color actCol,
	SDL_Color nactColor, bool act, int minScale, int maxScale, int curScale);
void UI_ComponentDraw(UI_Component& self);
