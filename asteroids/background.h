#pragma once
#include "texture.h"
#include "constants.h"

void BackgroundInit(Texture& texture, int index);
void BackgroundUpdate(Texture& texture, bool movementInX, bool movementInY, int sign, int speed = BACKOGRUND_MOVE_SPEED);