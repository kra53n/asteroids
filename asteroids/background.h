#pragma once
#include "config.h"
#include "texture.h"

void BackgroundInit(Texture& self, int index);
void BackgroundUpdate(Texture& self, Ship& ship);
void BackgroundDraw(Texture& self);