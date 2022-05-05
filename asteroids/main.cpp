#include "window.h"
#include "background.h"

#include <SDL.h>

struct Game {
    int wdt;
    int hgt;
    bool run = false;
    SDL_Event event;

    Texture background;
};

void GameInit(Game& game)
{
    game.run = true;

    BackgroundInit(game.background, 0);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    SDL_RenderCopy(ren, game.background.tex, NULL, &game.background.dstrect);

    SDL_RenderPresent(ren);
}

void GameUpdate(Game& game)
{
    while (SDL_PollEvent(&game.event))
    {
        int mouse_x; int mouse_y;

        switch (game.event.type)
        {
        case SDL_QUIT:
            game.run = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
            BackgroundUpdate(game.background, mouse_x, mouse_y, 10);
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
        SDL_Delay(20);
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