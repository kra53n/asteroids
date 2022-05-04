#include "window.h"
#include "stars.h"

#include <SDL.h>

struct Game {
    int wdt;
    int hgt;
    bool run = false;
    SDL_Event event;
};

void GameInit(Game& game)
{
    game.run = true;
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    SDL_RenderPresent(ren);
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
        }
    }
}

void GameLoop(Game& game)
{
    while (game.run)
    {
        GameUpdate(game);
        GameDraw(game);
        SDL_Delay(60);
    }
}

int main(int argc, char* artgv[])
{
    init();

    Game game;
    GameInit(game);
    GameLoop(game);

    deInit(0);
    return 0;
}