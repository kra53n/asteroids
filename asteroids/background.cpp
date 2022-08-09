#include <stdio.h>

#include "vector.h"
#include "structs.h"
#include "background.h"

void BackgroundInit(Texture& self, int index)
{
	if (index >= BACKGROUND_FILENAMES_NUM || index < 0)
	{
		printf("\nIndex error in BackgroundInit! Only [0;%d] possible, %d was put!\n", BACKGROUND_FILENAMES_NUM, index);
		system("pause");
		exit(1);
	}
	self = loadTexture(FILENAMES[index]);
}
