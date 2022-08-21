#pragma once
#include "structs.h"

void BulletsInit(Bullets& self);
void BulletsDestroy(Bullets& self);

void BulletsDelBullet(Bullets& self, Bullet* bullet);
void BulletsUpdate(Bullets& self, Ship& ship, Asteroids& asters, Keys& keys);
void BulletsDraw(Bullets& self);
