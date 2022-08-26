#pragma once
#include "texture.h"

struct Animation
{
    Texture* textures;
    int      frame;
    int      ticks;
};

void AnimationInit(Animation& self, int frames, const char* filename, const char* filenameType, int scaleCoeff);
