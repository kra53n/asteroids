#pragma once
#include <SDL_mixer.h>

struct Music
{
	const char* cur;
	Mix_Music* music = 0;
};

void MusicLoad(Music& self, const char* filename);
