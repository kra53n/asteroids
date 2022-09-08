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
    int          bulletType;
    bool         active;
    Vec          vel           = { 0, 0 };
    Vec          acc           = { 0, 0 };
};

void ShipInit(Ship& self, const char* filename, int instance);
void ShipReset(Ship& self, SDL_Point);

void ShipShoot(Ship& self, int type);
void ShipBulletsUpdate(Ship& ship, Asteroids& asters, SDL_Rect& enemyRect,
    int& enemyInited, Health& enemyHealth);

void ShipUpdate(Ship& self, Ship& ship, Asteroids& asters, SDL_Rect& enemyRect,
    Health& enemyHealth, bool& enemyActive, Keys& keys, int& gameState);
void ShipDraw(Ship& self, int gameState);

void ShipUpdateCollisionWithShip(Ship& s1, Ship& s2);
