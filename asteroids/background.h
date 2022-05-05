#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "texture.h"

#pragma once

const int BACKGROUND_FILENAMES_NUM = 3;
const int BACKOGRUND_MOVE_SPEED = 3;

const char FILENAMES[BACKGROUND_FILENAMES_NUM][41] = {
	"assets/images/stars/Nebula Aqua-Pink.png",
	"assets/images/stars/Nebula Blue.png",
	"assets/images/stars/Nebula Red.png"
};

void BackgroundInit(Texture& texture, int index);
void BackgroundUpdate(Texture& texture, int mouse_x, int mouse_y, int speed = BACKOGRUND_MOVE_SPEED);