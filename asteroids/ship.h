#pragma once
#include "score.h"
#include "vector.h"
#include "health.h"
#include "bullet.h"
#include "asteroid.h"
#include "animation.h"

struct Ship
{
    ShipActions  acts;
    Animation    engine;
    Texture      tex;
    Bullets      bullets;
    Health       health;
    Score        score;
    float        speedMovement = 0.5;
    float        rotationSpeed = 2.7;
    float        rotationCoeff = 0.1;
    int          rotationPower = 0;
    int          ticks         = 0;
    int          maxSpeed      = 10;
    int          instance;
    Vec          vel           = { 0, 0 };
    Vec          acc           = { 0, 0 };
};

void ShipInit(Ship& self, const char* filename, int instance);

void ShipShoot(Ship& self, int type);
void ShipBulletsUpdate(Ship& ship, Asteroids& asters, SDL_Rect& enemyRect, Health& enemyHealth, Keys& keys);

void ShipUpdate(Ship& self, Asteroids& asters, SDL_Rect& enemyRect, Health& enemyHealth, Keys& keys, int& gameState);
void ShipDraw(Ship& self, Keys& keys);
