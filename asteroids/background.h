#pragma once
#include "ship.h"
#include "config.h"
#include "texture.h"

void BackgroundInit(Texture& self, int index);

void ParticlesInit(Texture self[PARTICLES_FILENAMES_NUM]);
void ParticlesUpdate(Texture self[PARTICLES_FILENAMES_NUM], Vec& Vec);