#pragma once
#include "config.h"
#include "texture.h"

void BackgroundInit(Texture& texture, int index);
void BackgroundUpdate(Game& game);
void BackgroundDraw(Game& game);