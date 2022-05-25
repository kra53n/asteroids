#include "game.h"
#include "menu.h"
#include "background.h"

void GameInit(Game& game)
{
    game.run = true;
    BackgroundInit(game.background, 0);
    MenuInit(game.menu);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    SDL_RenderCopy(ren, game.background.tex, NULL, &game.background.dstrect);
    MenuDraw(game.menu);

    SDL_RenderPresent(ren);
}

void processKeys(Game& game)
{
    if (game.keysStatus.up)
    {
        BackgroundUpdate(game.background, 0, 1, -1);
    }
    if (game.keysStatus.down)
    {
        BackgroundUpdate(game.background, 0, 1, 1);
    }
    if (game.keysStatus.left)
    {
        BackgroundUpdate(game.background, 1, 0, -1);
    }
    if (game.keysStatus.right)
    {
        BackgroundUpdate(game.background, 1, 0, 1);
    }
}

void GameUpdate(Game& game)
{
    while (SDL_PollEvent(&game.event))
    {
        switch (game.event.type)
        {
        case SDL_QUIT:
            game.run = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&game.keysStatus.mouse_x, &game.keysStatus.mouse_y);
            break;
        case SDL_KEYDOWN:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                game.keysStatus.up = true;
                break;
            case SDL_SCANCODE_DOWN:
                game.keysStatus.down = true;
                break;
            case SDL_SCANCODE_LEFT:
                game.keysStatus.left = true;
                break;
            case SDL_SCANCODE_RIGHT:
                game.keysStatus.right = true;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                game.keysStatus.up = false;
                break;
            case SDL_SCANCODE_DOWN:
                game.keysStatus.down = false;
                break;
            case SDL_SCANCODE_LEFT:
                game.keysStatus.left = false;
                break;
            case SDL_SCANCODE_RIGHT:
                game.keysStatus.right = false;
                break;
            }
            break;
        }
    }
    processKeys(game);
    MenuProcess(game.menu, game.keysStatus);
}

void GameLoop(Game& game)
{
    while (game.run)
    {
        GameUpdate(game);
        GameDraw(game);
        SDL_Delay(20);
    }
}
