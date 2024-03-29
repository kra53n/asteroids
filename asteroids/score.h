#pragma once
#include <SDL.h>

#include "texture.h"

struct Score
{
    Texture   tex;
    int       point;
    char*     title;
};

void ScoreInit(Score& self, SDL_Point pos, int point, const char* title);
void ScoreDestroy(Score& self);

void ScoreUpdate(Score& self, int point = 0);
void ScoreDraw(Score& self);
