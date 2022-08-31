#pragma once
#include "config.h"
#include "texture.h"
#include "animation.h"

struct Asteroid
{
    SDL_Point pos;
    SDL_Rect  srcrect;
    SDL_Rect  dstrect;
    Vec       vel;
    int       type;
    int       frame;
    int       ticks;
    int       health;
    Asteroid* next;
    Asteroid* prev;
};

struct Asteroids
{
    Animation explosion;
    SDL_Point explosionPos;
    Texture   texture[ASTEROIDS_TYPE_NUM];
    int       frames[ASTEROIDS_TYPE_NUM];
    Asteroid* head                        = 0;
};

void AsteroidsInit(Asteroids& self, int asteroidsTpyesNum[ASTEROIDS_TYPE_NUM]);
void AsteroidsDestroy(Asteroids& self);

void AsteroidsPush(Asteroids& self, int type, int ticks);
void AsteroidsDelAsteroid(Asteroids& self, Asteroid* aster);
void AsteroidsUpdate(Asteroids& self);
void AsteroidsDraw(Asteroids& self);
