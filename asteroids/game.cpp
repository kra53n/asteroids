#include <time.h>
#include <stdlib.h>

#include "game.h"
#include "menu.h"
#include "ship.h"
#include "bullet.h"
#include "texture.h"
#include "asteroid.h"
#include "background.h"

void GameInit(Game& game)
{
    srand(time(0));

    game.run = true;
    BackgroundInit(game.background, 0);
    ParticlesInit(game.particles);
    BulletsInit(game.bullets);

    //int asteroidsTypes[ASTEROIDS_TYPE_NUM] = { 3, 2, 1, 1, 1, 1, 1, 1, 1 };
    int asteroidsTypes[ASTEROIDS_TYPE_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    AsteroidsInit(game.asteroids, asteroidsTypes);
    
    MenuInit(game.menu);
    ShipInit(game.ship, 100);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 17, 18, 55, 255);
    SDL_RenderClear(ren);

    TextureDrawAsInfiniteImage(game.background);
    TextureDrawAsInfiniteImage(game.particles[0]);
    switch (game.state)
    {
    case GAME_STATE_MENU: MenuDraw(game.menu); break;
    case GAME_STATE_PLAY:
        AsteroidsDraw(game.asteroids);
        BulletsDraw(game.bullets);
        ShipDraw(game.ship);
		TextureDrawAsInfiniteImage(game.particles[1]);
		TextureDrawAsInfiniteImage(game.particles[2]);
        break;
    }

    SDL_RenderPresent(ren);
}

void processKeys(Game& game)
{
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
        AsteroidsUpdate(game.asteroids);
        BulletsUpdate(game.bullets, game.ship, game.keysStatus);
        ShipUpdate(game.ship, game.asteroids, game.keysStatus);
        TextureUpdateAsInfiniteImage(
            game.background,
            { -game.ship.vel.x * game.ship.speedMovement, game.ship.vel.y * game.ship.speedMovement },
            VecGetLen(game.ship.vel)
        );
        ParticlesUpdate(game.particles, game.ship);
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
