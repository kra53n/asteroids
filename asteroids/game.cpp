#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "menu.h"
#include "ship.h"
#include "enemy.h"
#include "texture.h"
#include "asteroid.h"
#include "background.h"

void GameInit(Game& game)
{
    srand(time(0));

    game.run = true;
    BackgroundInit(game.background, 0);
    ParticlesInit(game.particles);

    //int asters[ASTEROIDS_TYPE_NUM] = { 9, 2, 1, 1, 1, 1, 1, 1, 1 };
    int asters[ASTEROIDS_TYPE_NUM] = { 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    //int asters[ASTEROIDS_TYPE_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    AsteroidsInit(game.asteroids, asters);
    
    MenuInit(game.menu);
    ShipInit(game.ship);
    EnemyInit(game.enemy);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    TextureDrawAsInfiniteImage(game.background);
    TextureDrawAsInfiniteImage(game.particles[0]);

    switch (game.state)
    {
    case GAME_STATE_MENU:
        MenuDraw(game.menu);
        break;

    case GAME_STATE_PLAY:
        AsteroidsDraw(game.asteroids);
        ShipDraw(game.ship, game.keys);
        EnemyDraw(game.enemy);
        TextureDrawAsInfiniteImage(game.particles[1]);
        TextureDrawAsInfiniteImage(game.particles[2]);
        break;
    }

    SDL_RenderPresent(ren);
}

void processKeys(Game& game)
{
    if (game.keys.escape)
    {
        game.keys.enter = false;
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
            SDL_GetMouseState(&game.keys.mouse_x, &game.keys.mouse_y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                game.keys.btnLeft = true;
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                game.keys.btnLeft = false;
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:     game.keys.up     = true; break;
            case SDL_SCANCODE_DOWN:   game.keys.down   = true; break;
            case SDL_SCANCODE_LEFT:   game.keys.left   = true; break;
            case SDL_SCANCODE_RIGHT:  game.keys.right  = true; break;

            case SDL_SCANCODE_W:      game.keys.up     = true; break;
            case SDL_SCANCODE_S:      game.keys.down   = true; break;
            case SDL_SCANCODE_A:      game.keys.left   = true; break;
            case SDL_SCANCODE_D:      game.keys.right  = true; break;

            case SDL_SCANCODE_RETURN: game.keys.enter  = true; break;
            case SDL_SCANCODE_SPACE:  game.keys.space  = true; break;
            case SDL_SCANCODE_ESCAPE: game.keys.escape = true; break;
            }
            break;

        case SDL_KEYUP:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:     game.keys.up     = false; break;
            case SDL_SCANCODE_DOWN:   game.keys.down   = false; break;
            case SDL_SCANCODE_LEFT:   game.keys.left   = false; break;
            case SDL_SCANCODE_RIGHT:  game.keys.right  = false; break;

            case SDL_SCANCODE_W:      game.keys.up     = false; break;
            case SDL_SCANCODE_S:      game.keys.down   = false; break;
            case SDL_SCANCODE_A:      game.keys.left   = false; break;
            case SDL_SCANCODE_D:      game.keys.right  = false; break;

            case SDL_SCANCODE_RETURN: game.keys.right  = false; break;
            case SDL_SCANCODE_SPACE:  game.keys.space  = false; break;
            case SDL_SCANCODE_ESCAPE: game.keys.escape = false; break;
            }
            break;
        }
    }
    processKeys(game);
    switch (game.state)
    {
    case GAME_STATE_MENU:
        MenuUpdate(game.menu, game.keys, game.state);
        break;

    case GAME_STATE_PLAY:
        AsteroidsUpdate(game.asteroids);
        ShipUpdate(game.ship, game.asteroids, game.enemy.tex.dstrect, game.enemy.health, game.keys, game.state);
        EnemyUpdate(game.enemy, game.ship);
        TextureUpdateAsInfiniteImage(
            game.background,
            { -game.ship.vel.x * game.ship.speedMovement, game.ship.vel.y * game.ship.speedMovement },
            VecGetLen(game.ship.vel)
        );
        ParticlesUpdate(game.particles, game.ship);
        break;

    case GAME_STATE_EXIT:
        game.run = false;
        break;
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
