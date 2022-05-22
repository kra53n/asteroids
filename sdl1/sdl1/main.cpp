#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "window.h"

struct KeysStatus
{
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

struct Texture
{
    SDL_Texture* tex;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
};

Texture loadTexture(const char filename[], int wdt=0, int hgt=0)
{
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf)
    {
        printf("\nError in loading image %s! Error: %s\n", filename, SDL_GetError());
        system("pause");
        exit(1);
    }

    Texture texture;
    texture.tex = SDL_CreateTextureFromSurface(ren, surf);

    float scaleCoeff = 1;
    if (!wdt) {wdt = surf->w; }
    else { scaleCoeff = (float)wdt / surf->w; }

    if (!hgt) { hgt = surf->h; }
    else { scaleCoeff = (float)hgt / surf->h; }
    texture.dstrect = { 0, 0, (int)(surf->w * scaleCoeff), (int)(surf->h * scaleCoeff) };
    
    SDL_FreeSurface(surf);
    
    return texture;
}

int main(int argc, char* artgv[])
{
    init();

    bool isRunning = true;
    SDL_Event event;
    KeysStatus keys;

    Texture textureExample = loadTexture("images/forest_background.jpg", 0, winHgt);
    Texture texturePlayer = loadTexture("images/player_animation.png", 0, 256);
    texturePlayer.srcrect = { 0, 0, 256, 256 };
    texturePlayer.dstrect = { 0, 0, texturePlayer.dstrect.h, texturePlayer.dstrect.h };
    bool animate = false;
    bool left = false;
    double speed = 500;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    int frame = 0;
    int frameCount = 6;
    int currentFrameTime = 0;
    int maxFrameTime = 100;
    int lastTicket = SDL_GetTicks();
    int deltaTime = 0;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    keys.up = true;
                    break;
                case SDL_SCANCODE_S:
                    keys.down = true;
                    break;
                case SDL_SCANCODE_A:
                    keys.left = true;
                    left = true;
                    break;
                case SDL_SCANCODE_D:
                    keys.right = true;
                    left = false;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    keys.up = false;
                    break;
                case SDL_SCANCODE_S:
                    keys.down = false;
                    break;
                case SDL_SCANCODE_A:
                    keys.left = false;
                    break;
                case SDL_SCANCODE_D:
                    keys.right = false;
                    break;
                }
                break;
            }
        }

        deltaTime = SDL_GetTicks() - lastTicket;
        lastTicket = deltaTime + lastTicket;

        SDL_SetRenderDrawColor(ren, 15, 15, 30, 255);
        SDL_RenderClear(ren);

        SDL_RenderCopy(ren, textureExample.tex, NULL, &textureExample.dstrect);

        int movement = int(speed * deltaTime / 1000.);
        if (keys.up)
            texturePlayer.dstrect.y -= movement;
        if (keys.down)
            texturePlayer.dstrect.y += movement;
        if (keys.left)
            texturePlayer.dstrect.x -= movement;
        if (keys.right)
            texturePlayer.dstrect.x += movement;

        animate = keys.down || keys.left || keys.up || keys.right;
        if (animate)
        {
            if (left) { flip = SDL_FLIP_HORIZONTAL; }
            else { flip = SDL_FLIP_NONE; }
            
            currentFrameTime += deltaTime;
            if (currentFrameTime >= maxFrameTime && (keys.left || keys.right))
            {
                currentFrameTime -= maxFrameTime;
                frame = (frame + 1) % frameCount;
                texturePlayer.srcrect.x = texturePlayer.srcrect.w * frame;
            }
        }


        SDL_RenderCopyEx(ren, texturePlayer.tex, &texturePlayer.srcrect, &texturePlayer.dstrect, 0, 0, flip);

        SDL_RenderPresent(ren);
    }

    deInit(0);

    return 0;
}