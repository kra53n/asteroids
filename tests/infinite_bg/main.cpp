#include <SDL.h>
#include <SDL_image.h>
#include "window.h"

struct Texture
{
    SDL_Texture* tex;
    SDL_Rect rect;
};

Texture loadTexture(const char filename[])
{
    SDL_Surface* surf = IMG_Load(filename);
    if (surf == NULL)
    {
        printf("Couldn`t load image %s! SDL Error: %s", filename, SDL_GetError());
        deInit(1);
        exit(1);
    }

    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(ren, surf);
    if (loadedTexture == NULL)
    {
        printf("Couldn't convert surface to texture in loadTexture function! Error: %s", SDL_GetError());
        deInit(1);
        exit(1);
    }
    SDL_FreeSurface(surf);

    Texture texture = { loadedTexture, { 0, 0, surf->w, surf->h } };
    return texture;
}

int run = true;
int drawing = true;

SDL_Event event;
bool left  = false;
bool right = false;
bool up    = false;
bool down  = false;

Texture background = loadTexture("assets/background.png");
int backgroundSpeed = 10;

void updateBackground()
{
    if (left)  background.rect.x += backgroundSpeed;
    if (right) background.rect.x -= backgroundSpeed;
    if (up)    background.rect.y += backgroundSpeed;
    if (down)  background.rect.y -= backgroundSpeed;

    if (background.rect.x < -background.rect.w
        || background.rect.x > background.rect.w)
        background.rect.x = 0;
    if (background.rect.y < -background.rect.h
        || background.rect.y > background.rect.h)
        background.rect.y = 0;
}

void drawBackground()
{
    SDL_Rect rect;
    int wdt = 0;
    int hgt = 0;
    
    if (background.rect.x < 0)
        wdt = background.rect.w;
    else if (background.rect.x > 0)
        wdt = -background.rect.w;

    if (background.rect.y < 0)
        hgt = background.rect.h;
    else if (background.rect.y > 0)
        hgt = -background.rect.h;

    SDL_RenderCopy(ren, background.tex, NULL, &background.rect);
    if (wdt)
    {
        rect = background.rect;
        rect.x += wdt;
        SDL_RenderCopy(ren, background.tex, NULL, &rect);
    }
    if (hgt)
    {
        rect = background.rect;
        rect.y += hgt;
        SDL_RenderCopy(ren, background.tex, NULL, &rect);
    }
    if (wdt && hgt)
    {
        rect = background.rect;
        rect.x += wdt;
        rect.y += hgt;
        SDL_RenderCopy(ren, background.tex, NULL, &rect);
    }
}

void update()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: run = false; break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_A: left  = true; break;
            case SDL_SCANCODE_D: right = true; break;
            case SDL_SCANCODE_W: up    = true; break;
            case SDL_SCANCODE_S: down  = true; break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_A: left  = false; break;
            case SDL_SCANCODE_D: right = false; break;
            case SDL_SCANCODE_W: up    = false; break;
            case SDL_SCANCODE_S: down  = false; break;
            }
            break;
        }
        updateBackground();
        drawing = true;
    }
}

void draw()
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderClear(ren);
    drawBackground();
    SDL_RenderPresent(ren);
    drawing = false;
}

int main(int argc, char* artgv[])
{
    while (run)
    {
        update();
        if (drawing)
            draw();
    }

    deInit(0);
    return 0;
}