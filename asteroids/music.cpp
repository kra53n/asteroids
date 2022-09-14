#include "music.h"

void MusicLoad(Music& self, const char* filename)
{
    if (self.music)
        Mix_FreeMusic(self.music);

    self.music = Mix_LoadMUS(filename);
    self.cur = filename;
    Mix_PlayMusic(self.music, -1);
}