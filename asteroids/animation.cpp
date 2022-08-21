#include <stdio.h>
#include <malloc.h>

#include "structs.h"
#include "animation.h"

void AnimationInit(Animation& self, int frames, const char* filename, const char* filenameType, int scaleCoeff)
{
	self.textures = (Texture*)malloc(sizeof(Texture) * frames);
	if (!self.textures) { exit(1); };

	char fullpath[50];
	for (int i = 0; i < frames; i++)
	{
		sprintf_s(fullpath, 50, "%s%d.%s", filename, i + 1, filenameType);
		self.textures[i] = loadTexture(fullpath);
        self.textures[i].dstrect.w *= scaleCoeff;
		self.textures[i].dstrect.h *= scaleCoeff;
	}

	self.ticks = SDL_GetTicks();
	self.frame = 0;
}
