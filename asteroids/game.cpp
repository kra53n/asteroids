#include "game.h"
#include "menu.h"
#include "ship.h"
#include "asteroid.h"
#include "background.h"

void GameInit(Game& game)
{
    game.run = true;
    //BackgroundInit(game.background, 0);
    AsteroidsInit(game);
    
    MenuInit(game.menu);
    ShipInit(game, 100);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    //SDL_RenderCopy(ren, game.background.tex, NULL, &game.background.dstrect);
    switch (game.state)
    {
    case GAME_STATE_MENU: MenuDraw(game.menu); break;
    case GAME_STATE_PLAY:
        AsteroidsDraw(game);
        ShipDraw(game);
        break;
    }

    SDL_RenderPresent(ren);
}

void processKeys(Game& game)
{
    //if (game.keysStatus.up)
    //{
    //    BackgroundUpdate(game.background, 0, 1, -1);
    //}
    //if (game.keysStatus.down)
    //{
    //    BackgroundUpdate(game.background, 0, 1, 1);
    //}
    //if (game.keysStatus.left)
    //{
    //    BackgroundUpdate(game.background, 1, 0, -1);
    //}
    //if (game.keysStatus.right)
    //{
    //    BackgroundUpdate(game.background, 1, 0, 1);
    //}
    if (game.keysStatus.escape)
    {
        game.keysStatus.enter = false;
        game.state = 0;
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
        case SDL_MOUSEBUTTONDOWN:
            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                game.keysStatus.btnLeft = true;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                game.keysStatus.btnLeft = false;
                break;
            }
            break;
        case SDL_KEYDOWN:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:     game.keysStatus.up     = true; break;
            case SDL_SCANCODE_DOWN:   game.keysStatus.down   = true; break;
            case SDL_SCANCODE_LEFT:   game.keysStatus.left   = true; break;
            case SDL_SCANCODE_RIGHT:  game.keysStatus.right  = true; break;

            case SDL_SCANCODE_W:      game.keysStatus.up     = true; break;
            case SDL_SCANCODE_S:      game.keysStatus.down   = true; break;
            case SDL_SCANCODE_A:      game.keysStatus.left   = true; break;
            case SDL_SCANCODE_D:      game.keysStatus.right  = true; break;

            case SDL_SCANCODE_RETURN: game.keysStatus.enter  = true; break;
            case SDL_SCANCODE_SPACE:  game.keysStatus.space  = true; break;
            case SDL_SCANCODE_ESCAPE: game.keysStatus.escape = true; break;
            }
            break;
        case SDL_KEYUP:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:     game.keysStatus.up     = false; break;
            case SDL_SCANCODE_DOWN:   game.keysStatus.down   = false; break;
            case SDL_SCANCODE_LEFT:   game.keysStatus.left   = false; break;
            case SDL_SCANCODE_RIGHT:  game.keysStatus.right  = false; break;

            case SDL_SCANCODE_W:      game.keysStatus.up     = false; break;
            case SDL_SCANCODE_S:      game.keysStatus.down   = false; break;
            case SDL_SCANCODE_A:      game.keysStatus.left   = false; break;
            case SDL_SCANCODE_D:      game.keysStatus.right  = false; break;

            case SDL_SCANCODE_RETURN: game.keysStatus.right  = false; break;
            case SDL_SCANCODE_SPACE:  game.keysStatus.space  = false; break;
            case SDL_SCANCODE_ESCAPE: game.keysStatus.escape = false; break;
            }
            break;
        }
    }
    processKeys(game);
    switch (game.state)
    {
    case GAME_STATE_MENU: MenuProcess(game); break;
    case GAME_STATE_PLAY:
        AsteroidsUpdate(game);
        ShipUpdate(game);
        break;
    case GAME_STATE_EXIT: game.run = false;  break;
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
