#pragma once
#include <SDL.h>

enum UI_Comps { Text, Button, CheckButton, Scale, };

struct UI_Entity
{
	const char* text;
	SDL_Color&  actCol;
	SDL_Color&  nactCol;
};

typedef UI_Entity UI_Text;

struct UI_Button
{
	UI_Entity entity;
	bool      act;
};

typedef UI_Entity UI_Button;

struct Scale
{
	UI_Entity entity;
	SDL_Rect  rect;
	int       max;
	int       min;
	int       cur;
};
