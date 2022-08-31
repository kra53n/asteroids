#include <SDL.h>
#include <stdio.h>

#include "ship.h"
#include "funcs.h"
#include "enemy.h"
#include "health.h"
#include "bullet.h"
#include "window.h"
#include "texture.h"

void EnemyInit(Enemy& self)
{
    self.tex = loadTexture(ENEMY_FILENAME);
    self.tex.dstrect.w *= ENEMY_SCALE_COEFF;
    self.tex.dstrect.h *= ENEMY_SCALE_COEFF;

    self.ticks = SDL_GetTicks();
    self.damageTicks = self.ticks;

    BulletsInit(self.bullets);
    HealthInit(self.health);
}

void EnemyDestroy(Enemy& self)
{
    SDL_DestroyTexture(self.tex.tex);
}

bool EnemyIsCloseWithShip(Enemy& self, Ship& ship)
{
    return isCircsColliding(
        getRectCenter(self.tex.dstrect), getRadius(self.tex.dstrect),
        getRectCenter(ship.tex.dstrect), getRadius(ship.tex.dstrect)
    );
}

void EnemyUpdateMovement(Enemy& self, Ship& ship)
{
    if (EnemyIsCloseWithShip(self, ship))
    {
        self.vel.x += self.acc.x / 0.7;
        self.vel.y += self.acc.y / 0.7;
        VecSetAngle(self.vel, VecGetAngle(self.vel) + 15);
    }

    self.vel.x += self.acc.x;
    self.vel.y += self.acc.y;
    VecSetLen(self.acc, VecGetLen(self.acc) + 0.1);

    self.tex.dstrect.x += self.vel.x;
    self.tex.dstrect.y += self.vel.y;
}

void EnemySetDirectoin(Enemy& self, Ship& ship)
{
    VecSetAngleByCoords(self.vel, getRectCenter(self.tex.dstrect), getRectCenter(ship.tex.dstrect));
    VecSetLen(self.vel, 5);

    VecSetAngle(self.acc, -VecGetAngle(self.vel));
    VecSetLen(self.acc, 0.1);
}

void EnemyShoot(Enemy& self)
{
    if (SDL_GetTicks() % 50) return;

    for (int i = 0; i < 360; i += 45)
    {
        Vec pos;
        Bullet* bullet = BulletsPush(self.bullets, self.tex, 2, BULLET_ENEMY_AFFILIATION);
        float angle = VecGetAngle(bullet->vel) + i;

        VecSetLen(pos, getRadius(self.tex.dstrect));

        VecSetAngle(bullet->vel, angle);
        VecSetAngle(pos, angle);

        bullet->pos = getRectCenter(self.tex.dstrect);
        bullet->pos.x += pos.x;
        bullet->pos.y += pos.y;
        bullet->affiliation = BULLET_ENEMY_AFFILIATION;
    }
}

void EnemyUpdateCollisionWithShip(Enemy& self, Ship& ship)
{
    if (!isCircsColliding(
        getRectCenter(self.tex.dstrect), getRadius(self.tex.dstrect),
        getRectCenter(ship.tex.dstrect), getRadius(ship.tex.dstrect)
    )) return;

    HealthUpdate(ship.health, ENEMY_DAMAGE);
}

bool EnemyUpdateBulletIollisionWithShip(Enemy& self, Bullet* bullet, Ship& ship)
{
    if (!isPointInCirc(
        getRectCenter(ship.tex.dstrect),
        getRadius(ship.tex.dstrect),
        { bullet->pos.x, bullet->pos.y }
    )) return false;

    HealthUpdate(ship.health, ENEMY_BULLET_DAMAGE);
    BulletsDelBullet(self.bullets, bullet);

    return true;
}

void EnemyUpdateBullets(Enemy& self, Ship& ship)
{
    for (Bullet* cur = self.bullets.head; cur;)
    {
        Bullet* curNext = cur->next;

        cur->pos.x += cur->vel.x;
        cur->pos.y += cur->vel.y;

        if (EnemyUpdateBulletIollisionWithShip(self, cur, ship))
        {
            cur = curNext;
            continue;
        }

        cur = curNext;
    }
}

void EnemyUpdate(Enemy& self, Ship& ship)
{
    EnemyUpdateMovement(self, ship);
    EnemyShoot(self);
    EnemyUpdateBullets(self, ship);
    EnemyUpdateCollisionWithShip(self, ship);
    boundScreen(self.tex.dstrect);

    int ticks = SDL_GetTicks();
    if (ticks - self.ticks >= ENEMY_DELAY) self.ticks = ticks;
    else return;

    EnemySetDirectoin(self, ship);
}

void EnemyDraw(Enemy& self)
{
    SDL_RenderCopy(ren, self.tex.tex, 0, &self.tex.dstrect);
    BulletsDraw(self.bullets);
}
