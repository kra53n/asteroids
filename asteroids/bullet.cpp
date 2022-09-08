#include <SDL.h>
#include <stdio.h>
#include <malloc.h>

#include "score.h"
#include "funcs.h"
#include "vector.h"
#include "window.h"
#include "config.h"
#include "bullet.h"
#include "asteroid.h"

void BulletsInit(Bullets& self)
{
    for (int i = 0; i < BULLETS_TYPE_NUM; i++)
    {
        self.texs[i] = loadTexture(BULLETS[i].filename);
        self.texs[i].dstrect.w *= SHIP_SCALE_COEFF;
        self.texs[i].dstrect.h *= SHIP_SCALE_COEFF;
    }
}

void BulletsDestroy(Bullets& self)
{
    for (int i = 0; i < BULLETS_TYPE_NUM; i++)
    {
        SDL_DestroyTexture(self.texs[i].tex);
    }
}

void BulletsClear(Bullets& self)
{
    for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
    {
        free(cur);
    }
    self.head = NULL;
}

Bullet* BulletsGetNewBullet(Bullets& self, Texture& tex, int type, int affiliation)
{
    Bullet* elem = (Bullet*)malloc(sizeof(Bullet));

    if (!elem)
    {
        printf("\nMemory allocation error in BulletsGetNewBullet");
        deInit(1);
    }

    VecSetLen(elem->vel, BULLETS[type].speed);
    VecSetAngle(elem->vel, tex.angle);

    Vec pos;
    VecSetLen(pos, tex.dstrect.w / 2);
    VecSetAngle(pos, -tex.angle);

    elem->pos = {
        (int)(tex.dstrect.x + tex.dstrect.w / 2 + pos.x),
        (int)(tex.dstrect.y + tex.dstrect.h / 2 + pos.y),
    };

    elem->ticks = SDL_GetTicks();
    elem->affiliation = affiliation;
    elem->type = type;
    elem->next = NULL;

    return elem;
}

Bullet* BulletsPush(Bullets& self, Texture& tex, int type, int affiliation)
{
    Bullet* elem = BulletsGetNewBullet(self, tex, type, affiliation);

    for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
    {
        if (cur->next == NULL)
        {
            elem->prev = cur;
            cur->next = elem;
            break;
        }
    }

    if (self.head == NULL)
    {
        elem->prev = NULL;
        self.head = elem;
    }

    return elem;
}

void BulletsDelBullet(Bullets& self, Bullet* bullet)
{
    if (bullet->next == NULL)
    {
        if (bullet->prev == NULL)
            self.head = NULL;
        else
            bullet->prev->next = NULL;
    }
    else if (self.head == bullet)
    {
        self.head = bullet->next;
        self.head->prev = NULL;
    }
    else
    {
        bullet->prev->next = bullet->next;
        bullet->next->prev = bullet->prev;
    }

    free(bullet);
}

// NOTE: move it to ship.cpp
// return status of collision
bool BulletsUpdateCollisionWithAstroids(Bullets& self, Bullet* bullet, Asteroids& asters, Score& score)
{
    for (Asteroid* aster = asters.head; aster != NULL; aster = aster->next)
    {
        int asterR = getRadius(asters.texture[aster->type].dstrect);

        if (!isPointInCirc(
            { aster->pos.x + asterR, aster->pos.y + asterR },
            asterR,
            { bullet->pos.x, bullet->pos.y }
        )) continue;
        
        aster->health -= BULLETS[bullet->type].damage;
        if (aster->health <= 0)
        {
            ScoreUpdate(score, ASTEROIDS[aster->type].health);
            AsteroidsDelAsteroid(asters, aster);
        }
        BulletsDelBullet(self, bullet);

        return true;
    }
}

void BulletsDraw(Bullets& self)
{
    SDL_Point nullPoint = { 0, 0 };

    for (Bullet* cur = self.head; cur != NULL; cur = cur->next)
    {
        Texture tex = self.texs[cur->type];
        SDL_Rect rect = { cur->pos.x, cur->pos.y, tex.dstrect.w, tex.dstrect.h };
        SDL_Point center = { 0, self.texs[cur->type].dstrect.h / 2 };
        SDL_RenderCopyEx(ren, tex.tex, 0, &rect, VecGetAngle(cur->vel), &center, SDL_FLIP_NONE);
    }
}
