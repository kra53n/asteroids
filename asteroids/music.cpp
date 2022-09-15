#include "music.h"
#include "config.h"

MUSIC_EFFECT_INFO MusicEffects[MUSIC_EFFECTS_NUM] = {
    { MUSIC_BULLET_1,     "assets/audio/effects/bullet1.wav",      0 },
    { MUSIC_BULLET_2,     "assets/audio/effects/bullet2.wav",      0 },
    { MUSIC_BUTTON,       "assets/audio/effects/button.wav",       0 },
    { MUSIC_COLLIDED,     "assets/audio/effects/collided.wav",     0 },
    { MUSIC_DESTROYED,    "assets/audio/effects/destroyed.wav",    0 },
    { MUSIC_BULLET_ENEMY, "assets/audio/effects/bullet_enemy.wav", 0 },
    { MUSIC_LOOSE,        "assets/audio/effects/loose.wav",        0 },
};

void MusicEffectsInit()
{
    for (int i = 0; i < MUSIC_EFFECTS_NUM; i++)
        MusicEffects[i].chunk = Mix_LoadWAV(MusicEffects[i].filename);
}

void MusicEffectsPlay(int effect)
{
    for (int i = 0; i < MUSIC_EFFECTS_NUM; i++)
    {
        if (i != effect) continue;
        Mix_HaltChannel(-1);
        Mix_PlayChannel(-1, MusicEffects[i].chunk, 0);
        break;
    }
}

void MusicLoad(Music& self, const char* filename)
{
    if (self.music)
        Mix_FreeMusic(self.music);

    self.music = Mix_LoadMUS(filename);
    self.cur = filename;
    Mix_PlayMusic(self.music, -1);
}

void MusicDestroy(Music& self)
{
    Mix_FreeMusic(self.music);
    for (int i = 0; i < MUSIC_EFFECTS_NUM; i++)
        Mix_FreeChunk(MusicEffects[i].chunk);
}