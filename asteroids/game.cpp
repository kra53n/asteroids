#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "menu.h"
#include "enemy.h"
#include "config.h"
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
    
    MenuInit(game.menu, MAIN_MENU, MAIN_MENU_NUM);
    ShipInit(game.ship1, SHIP_FILENAME1, SHIP1);
    ShipInit(game.ship2, SHIP_FILENAME2, SHIP2);
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
    case GAME_STATE_PLAY:
        MenuDraw(game.menu);
        break;

    case GAME_STATE_SOLO:
        AsteroidsDraw(game.asteroids);
        ShipDraw(game.ship1, game.state);
        EnemyDraw(game.enemy);
        TextureDrawAsInfiniteImage(game.particles[1]);
        TextureDrawAsInfiniteImage(game.particles[2]);
        break;

    case GAME_STATE_SEAT:
        AsteroidsDraw(game.asteroids);
        ShipDraw(game.ship1, game.state);
        ShipDraw(game.ship2, game.state);
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
        game.state = GAME_STATE_MENU;
        MenuInit(game.menu, MAIN_MENU, MAIN_MENU_NUM);
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
                game.keys.leftClick = true;
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                game.keys.leftClick = false;
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:       game.keys.w      = true; break;
            case SDL_SCANCODE_S:       game.keys.s      = true; break;
            case SDL_SCANCODE_A:       game.keys.a      = true; break;
            case SDL_SCANCODE_D:       game.keys.d      = true; break;
            case SDL_SCANCODE_SPACE:   game.keys.space  = true; break;

            case SDL_SCANCODE_UP:      game.keys.up     = true; break;
            case SDL_SCANCODE_DOWN:    game.keys.down   = true; break;
            case SDL_SCANCODE_LEFT:    game.keys.left   = true; break;
            case SDL_SCANCODE_RIGHT:   game.keys.right  = true; break;
            case SDL_SCANCODE_RCTRL:   game.keys.rctrl  = true; break;

            case SDL_SCANCODE_RETURN:  game.keys.enter  = true; break;
            case SDL_SCANCODE_RETURN2: game.keys.enter  = true; break;
            case SDL_SCANCODE_ESCAPE:  game.keys.escape = true; break;
            }
            break;

        case SDL_KEYUP:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:       game.keys.w      = false; break;
            case SDL_SCANCODE_S:       game.keys.s      = false; break;
            case SDL_SCANCODE_A:       game.keys.a      = false; break;
            case SDL_SCANCODE_D:       game.keys.d      = false; break;
            case SDL_SCANCODE_SPACE:   game.keys.space  = false; break;

            case SDL_SCANCODE_UP:      game.keys.up     = false; break;
            case SDL_SCANCODE_DOWN:    game.keys.down   = false; break;
            case SDL_SCANCODE_LEFT:    game.keys.left   = false; break;
            case SDL_SCANCODE_RIGHT:   game.keys.right  = false; break;
            case SDL_SCANCODE_RCTRL:   game.keys.rctrl  = false; break;

            case SDL_SCANCODE_RETURN:  game.keys.enter  = false; break;
            case SDL_SCANCODE_ESCAPE:  game.keys.escape = false; break;
            }
            break;
        }

        processKeys(game);
    }

    switch (game.state)
    {
    case GAME_STATE_MENU:
    case GAME_STATE_PLAY:
        MenuUpdate(game.menu, game.keys, game.state);

        switch (game.state)
        {
        case GAME_STATE_PLAY:
            game.menu.restart = true;

            break;
        }

        break;

    case GAME_STATE_SOLO:
        if (game.menu.restart)
        {
            game.menu.restart = false;

            ShipReset(game.ship1, { winWdt2, winHgt2 });
            game.ship2.active = false;
        }

        AsteroidsUpdate(game.asteroids);
        ShipUpdate(game.ship1, game.ship2, game.asteroids, game.enemy.tex.dstrect,
            game.enemy.health, game.keys, game.state);
        EnemyUpdate(game.enemy, game.ship1);
        TextureUpdateAsInfiniteImage(
            game.background,
            { -game.ship1.vel.x * game.ship1.speedMovement, game.ship1.vel.y * game.ship1.speedMovement },
            VecGetLen(game.ship1.vel)
        );
        ParticlesUpdate(game.particles, game.ship1);
        break;

    case GAME_STATE_SEAT:
        if (game.menu.restart)
        {
            game.menu.restart = false;

            int distance = 100;
            ShipReset(game.ship1, { winWdt2 - distance, winHgt2 });
            ShipReset(game.ship2, { winWdt2 + distance, winHgt2 });
            game.ship2.tex.angle = 180;
            game.ship2.health.rect.x = winWdt - game.ship2.health.rect.x - game.ship2.health.rect.w;
        }

        AsteroidsUpdate(game.asteroids);
        ShipUpdate(game.ship1, game.ship2, game.asteroids, game.enemy.tex.dstrect,
            game.enemy.health, game.keys, game.state);
        ShipUpdate(game.ship2, game.ship1, game.asteroids, game.enemy.tex.dstrect,
            game.enemy.health, game.keys, game.state);
        //EnemyUpdate(game.enemy, game.ship1);
        TextureUpdateAsInfiniteImage(
            game.background,
            { -game.ship1.vel.x * game.ship1.speedMovement, game.ship1.vel.y * game.ship1.speedMovement },
            VecGetLen(game.ship1.vel)
        );
        ParticlesUpdate(game.particles, game.ship1);
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
