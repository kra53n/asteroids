#include "background.h"

#pragma once

void BackgroundInit(Texture& texture, int index)
{
	if (index >= BACKGROUND_FILENAMES_NUM || index < 0)
	{
		printf("\nIndex error in Background init! Put %d index. Only [0;%d] possible!", index, BACKGROUND_FILENAMES_NUM);
		system("pause");
		exit(1);
	}
	texture = loadTexture(FILENAMES[index]);
	texture.dstrect.x = -400;
	texture.dstrect.y = -400;
}

void BackgroundUpdate(Texture& texture, int mouse_x, int mouse_y, int speed)
{
	if (mouse_x > 0) { texture.dstrect.x -= speed; }
	if (mouse_x < 0) { texture.dstrect.x += speed; }

	if (mouse_y > 0) { texture.dstrect.y -= speed; }
	if (mouse_y < 0) { texture.dstrect.y += speed; }
}