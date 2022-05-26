#include <stdio.h>
#include "background.h"

void BackgroundInit(Texture& texture, int index)
{
	if (index >= BACKGROUND_FILENAMES_NUM || index < 0)
	{
		printf("\nIndex error in BackgroundInit! Only [0;%d] possible, %d was put!\n", BACKGROUND_FILENAMES_NUM, index);
		system("pause");
		exit(1);
	}
	texture = loadTexture(FILENAMES[index]);
	texture.dstrect.x = -1200;
	texture.dstrect.y = -1800;
}

void BackgroundUpdate(Texture& texture, bool movementInX, bool movementInY, int sign, int speed)
{
	if (movementInX)
	{
		if (sign > 0) { texture.dstrect.x -= speed; }
		if (sign < 0) { texture.dstrect.x += speed; }
	}

	if (movementInY)
	{
		if (sign > 0) { texture.dstrect.y -= speed; }
		if (sign < 0) { texture.dstrect.y += speed; }
	}
}