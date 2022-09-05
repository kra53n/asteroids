#include <stdio.h>

#include "vector.h"
#include "texture.h"
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

void ParticlesInit(Texture self[PARTICLES_FILENAMES_NUM])
{
    for (int i = 0; i < PARTICLES_FILENAMES_NUM; i++)
        self[i] = loadTexture(PARTICLES_FILENAMES[i]);
}

void ParticlesUpdate(Texture self[PARTICLES_FILENAMES_NUM], Vec& vec)
{
    float speed = 0.3;

    for (int i = 0; i < PARTICLES_FILENAMES_NUM; i++, speed += 0.6)
    {
        Vec offset = vec;
        float offsetLen = VecGetLen(offset);

        if (offsetLen >= 5)
            VecSetLen(offset, offsetLen);
        else
            VecSetLen(offset, 2 + speed);

        TextureUpdateAsInfiniteImage(self[i], { -offset.x, -offset.y });
    }
}

void ParticlesDraw(Texture self[PARTICLES_FILENAMES_NUM])
{
    for (int i = 0; i < PARTICLES_FILENAMES_NUM; i++)
        TextureDrawAsInfiniteImage(self[i]);
}
