#pragma once
#include "config.h"
#include "texture.h"

void BackgroundInit(Texture& self, int index);

void ParticlesInit(Texture self[PARTICLES_FILENAMES_NUM]);
void ParticlesUpdate(Texture self[PARTICLES_FILENAMES_NUM], Ship& ship);