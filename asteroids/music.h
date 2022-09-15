#pragma once
#include <SDL_mixer.h>

#include "config.h"

struct Music
{
    const char*  cur;
    Mix_Music*   music = 0;
};

void MusicEffectsInit();
void MusicEffectsPlay(int effect);

void MusicLoad(Music& self, const char* filename);

void MusicDestroy(Music& self);
