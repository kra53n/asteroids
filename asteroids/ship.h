#pragma once
#include "score.h"
#include "vector.h"
#include "health.h"
#include "bullet.h"
#include "asteroid.h"
#include "animation.h"

struct Ship
{
    Animation engine;
    Texture   tex;
    Score     score;
    Health    health;
    float     speedMovement = 0.5;
    float     rotationSpeed = 2.7;
    float     rotationCoeff = 0.1;
    int       rotationPower = 0;
    int       ticks         = 0;
    int       bulletTicks   = 0;
    int       maxSpeed      = 10;
    Vec       vel           = { 0, 0 };
    Vec       acc           = { 0, 0 };
};

void ShipInit(Ship& self);

void ShipShoot(Ship& self, Bullets& bullets, int type);
void ShipBulletsUpdate(Bullets& self, Ship& ship, Asteroids& asters, Keys& keys);

void ShipUpdate(Ship& self, Asteroids& asters, Bullets& bullets, Keys& keys, int& gameState);
void ShipDraw(Ship& self, Keys& keys);
