#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "menu.h"
#include "level.h"
#include "funcs.h"
#include "enemy.h"
#include "record.h"
#include "config.h"
#include "texture.h"
#include "asteroid.h"
#include "background.h"

void GameInit(Game& game)
{
    srand(time(0));

    game.run = true;
    game.levels = LevelLoadFile(LEVEL_FILE_FILENAME);
    
    BackgroundInit(game.background, 0);
    ParticlesInit(game.particles);
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

    case GAME_STATE_LEVELS:
        if (game.levels.inited)
            LevelDraw(game.levels);
        break;

    case GAME_STATE_SOLO:
        AsteroidsDraw(game.asteroids);
        ShipDraw(game.ship1, game.state);
        EnemyDraw(game.enemy);
        TextureDrawAsInfiniteImage(game.particles[1]);
        TextureDrawAsInfiniteImage(game.particles[2]);
        break;

    case GAME_STATE_SEAT:
        ShipDraw(game.ship1, game.state);
        ShipDraw(game.ship2, game.state);
        TextureDrawAsInfiniteImage(game.particles[1]);
        TextureDrawAsInfiniteImage(game.particles[2]);
        break;

    case GAME_STATE_ABOUT:
    case GAME_STATE_LOOSE:
    case GAME_STATE_WIN:
    case GAME_STATE_PLAYER1_WIN:
    case GAME_STATE_PLAYER2_WIN:
        SDL_RenderCopy(ren, game.messageTexture.tex, 0, &game.messageTexture.dstrect);
        break;
    }

    SDL_RenderPresent(ren);
}

void updateMessageTexture(Texture& tex, const char* message,
    const char* fontname = MENU_FONTNAME, int size = MENU_FONT_SIZE)
{
    if (tex.tex)
        SDL_DestroyTexture(tex.tex);
    tex = loadFont(message, fontname, COLOR_OF_NON_ACTIVE_OPTION, size);
}

void processKeys(Game& game)
{
    if (game.keys.escape)
    {
        game.keys.enter = false;
        game.state = GAME_STATE_MENU;
        MenuInit(game.menu, MAIN_MENU, MAIN_MENU_NUM);

        game.levels.inited = false;
    }
}

int GameUpdateSoloStateGetBonusTime(Game& game)
{
    int ticks = SDL_GetTicks();
    int timeSpent = ticks - game.levels.ticks;
    return timeSpent <= LEVEL_BONUS_TIME ?
        (LEVEL_BONUS_TIME - timeSpent) / LEVEL_BONUS_TIME_COEFF : 0;
}

void GameUpdateSoloStateLoose(Game& game)
{
    if (game.ship1.health.point > 0) return;
    game.state = GAME_STATE_LOOSE;

    char message[80];
    sprintf_s(message, 80, "ur score: %d\nbest score: %d\nur position in top: %d",
        game.ship1.score.point,
        getBestScore(game.levels.cur + 1, game.ship1.score.point),
        getPosInLevelRecords(game.levels.cur+1, game.ship1.score.point) + 1);
    writeScore(game.levels.cur + 1, game.ship1.score.point);
    updateMessageTexture(game.messageTexture, message, MENU_FONTNAME, 40);

    centerizeRect(game.messageTexture.dstrect, winRect);
}

void GameUpdateSoloStateWin(Game& game)
{
    if (game.enemy.active || game.asteroids.head) return;

    game.state = GAME_STATE_WIN;
    int score = game.ship1.score.point + GameUpdateSoloStateGetBonusTime(game);

    char message[100];
    sprintf_s(message, 100, "You have passed\nur score: %d\nbest score: %d\nur position in top: %d",
        score,
        getBestScore(game.levels.cur + 1, score),
        getPosInLevelRecords(game.levels.cur+1, score) + 1);
    writeScore(game.levels.cur + 1, score);
    updateMessageTexture(game.messageTexture, message, MENU_FONTNAME, 40);

    centerizeRect(game.messageTexture.dstrect, winRect);
}

void GameUpdateSoloState(Game& game)
{
    if (game.menu.restart)
    {
        game.menu.restart = false;

        ShipReset(game.ship1, { winWdt2, winHgt2 });
        game.ship2.active = false;

        game.ship1.health.rect.y = 50;
    }

    AsteroidsUpdate(game.asteroids);
    ShipUpdate(game.ship1, game.ship2, game.asteroids, game.enemy.tex.dstrect,
        game.enemy.health, game.enemy.active, game.keys, game.state);
    EnemyUpdate(game.enemy, game.ship1);

    TextureUpdateAsInfiniteImage(game.background,
        { -game.ship1.vel.x * (float)0.5, game.ship1.vel.y * (float)0.5 },
        VecGetLen(game.ship1.vel));

    ParticlesUpdate(game.particles, game.ship1.vel);

    GameUpdateSoloStateLoose(game);
    GameUpdateSoloStateWin(game);

}

void GameUpdateSeatState(Game& game)
{
    if (game.menu.restart)
    {
        game.menu.restart = false;

        int distance = 100;
        ShipReset(game.ship1, { winWdt2 - distance, winHgt2 });
        ShipReset(game.ship2, { winWdt2 + distance, winHgt2 });
        game.ship2.tex.angle = 180;
        game.ship2.health.rect.x = winWdt - game.ship2.health.rect.x - game.ship2.health.rect.w;

        game.ship1.health.rect.y = 10;
        game.ship2.health.rect.y = 10;
    }

    ShipUpdate(game.ship1, game.ship2, ASTEROIDS_EMPTY, game.enemy.tex.dstrect,
        game.enemy.health, game.enemy.active, game.keys, game.state);
    ShipUpdate(game.ship2, game.ship1, ASTEROIDS_EMPTY, game.enemy.tex.dstrect,
        game.enemy.health, game.enemy.active, game.keys, game.state);

    TextureUpdateAsInfiniteImage(game.background,
        getMiddlePointBetweenShips(game.ship1, game.ship2), VecGetLen(game.ship1.vel));

    ParticlesUpdate(game.particles, VecGetMaxVec(game.ship1.vel, game.ship2.vel));

    if (game.ship1.health.point < 0 || game.ship2.health.point < 0)
    {
        game.state = game.ship1.health.point < 0 ? GAME_STATE_PLAYER2_WIN : GAME_STATE_PLAYER1_WIN;
        const char* message = GAME_STATE_PLAYER1_WIN ? "1st player won" : "2nd player won";
        if (game.ship1.health.point == 0 && game.ship2.health.point == 0)
            message = "its draw";
        updateMessageTexture(game.messageTexture, message);
        centerizeRect(game.messageTexture.dstrect, winRect);
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
        game.aboutInited = false;

        switch (game.state)
        {
        case GAME_STATE_PLAY:
            game.menu.restart = true;
            break;
        }
        break;

    case GAME_STATE_LEVELS:
        if (!game.levels.inited)
            LevelInit(game.levels);
        LevelUpdate(game.levels, game.asteroids, game.enemy, game.keys, game.state);
        break;

    case GAME_STATE_SOLO: GameUpdateSoloState(game); break;
    case GAME_STATE_SEAT: GameUpdateSeatState(game); break;
    
    case GAME_STATE_ABOUT:
    case GAME_STATE_LOOSE:
    case GAME_STATE_WIN:
    case GAME_STATE_PLAYER1_WIN:
    case GAME_STATE_PLAYER2_WIN:
        switch (game.state)
        {
        case GAME_STATE_ABOUT:
            if (!game.aboutInited)
            {
                game.aboutInited = true;
                updateMessageTexture(game.messageTexture, ABOUT_MESSAGE, ABOUT_FONTNAME, 35);
                centerizeRect(game.messageTexture.dstrect, winRect);
            }
            break;
        }

        if (game.keys.enter)
        {
            int ticks = SDL_GetTicks();
            if (ticks - game.menu.ticks < MENU_DELAY_BUTTONS) return;
            game.menu.ticks = ticks;

            game.state = GAME_STATE_MENU;
            game.menu.restart = true;
        }
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
