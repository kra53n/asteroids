#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL.h>

#include "menu.h"
#include "music.h"
#include "enemy.h"
#include "funcs.h"
#include "level.h"
#include "config.h"
#include "window.h"
#include "texture.h"
#include "asteroid.h"

LevelState readState(LevelState state, char const* string);
void processState(LevelState state, const char* string, Level& level);

void printLevels(Levels& self)
{
    for (int i = 0; i < self.num; i++)
    {
        printf("\nlevel num: %d", self.levels[i].num);
    }
}

Levels LevelLoadFile(const char* filename)
{
    FILE* f;
    if (fopen_s(&f, filename, "r"))
    {
        char message[120];
        sprintf_s(message, 120, "Error while trying to read file with filename: %s in LevelLoadFile", filename);
        logError(message);
    }

    Levels levels;
    Level levelInfo = LEVEL_STANDART_INFO;

    LevelState state = LEVEL_STATE;
    LevelState tmpState = state;

    while (!feof(f))
    {
        char string[120];
        fscanf_s(f, "%s", string, 120);

        state = readState(state, string);
        if (state != tmpState)
        {
            tmpState = state;
            continue;
        }

        if (state == LEVEL_NUM)
        {
            levels.levels = (Level*)realloc(levels.levels, sizeof(Level) * (levels.num + 1));
            if (levels.num)
                levels.levels[levels.num-1] = levelInfo;
            levelInfo = LEVEL_STANDART_INFO;
            levels.num++;
        }

        processState(state, string, levelInfo);
    }
    levels.levels[levels.num-1] = levelInfo;

    fclose(f);

    return levels;
}

LevelState readState(LevelState state, char const* string)
{
    if      (!strcmp(string, "level"))      return LEVEL_NUM;
    else if (!strcmp(string, "asteroids"))  return LEVEL_ASTEROIDS;
    else if (!strcmp(string, "enemy"))      return LEVEL_ENEMY;
    else if (!strcmp(string, "background")) return LEVEL_BACKGROUND;
    return state;
}

void processNumState(const char* string, Level& level);
void processAsteroidsState(const char* string, Level& level);
void processEnemyState(const char* string, Level& level);
void processBackgroundState(const char* string, Level& level);

void processState(LevelState state, const char* string, Level& level)
{
    switch (state)
    {
    case LEVEL_NUM:        processNumState(string, level);        break;
    case LEVEL_ASTEROIDS:  processAsteroidsState(string, level);  break;
    case LEVEL_ENEMY:      processEnemyState(string, level);      break;
    case LEVEL_BACKGROUND: processBackgroundState(string, level); break;
    }
}

void processNumState(const char* string, Level& level)
{
    level.num = atoi(string);
}

void processAsteroidsState(const char* string, Level& level)
{
    if (level.asters[ASTEROIDS_TYPE_NUM-1])
        return;

    static int idx = 0;
    static int levelNum = level.num;

    if (levelNum != level.num)
    {
        levelNum = level.num;
        idx = 0;
    }

    if (level.asters[idx])
    {
        idx++;
        return;
    }

    level.asters[idx] = atoi(string);
    idx++;
}

void processEnemyState(const char* string, Level& level)
{
    level.enemy = atoi(string);
}

void processBackgroundState(const char* string, Level& level)
{
    level.bgNum = atoi(string) - 1;
}

void LevelInit(Levels& levels)
{
    levels.inited = true;
    levels.cur = 0;
    levels.ticks = SDL_GetTicks();

    levels.numTextures = (Texture*)malloc(sizeof(Texture) * levels.num);

    for (int i = 0; i < levels.num; i++)
    {
        char num[4];
        sprintf_s(num, "%d", levels.levels[i].num, 3);

        levels.numTextures[i] = loadFont(num, MENU_FONTNAME,
            COLOR_OF_NON_ACTIVE_OPTION, LEVEL_FONT_SIZE);

        if (i == 0)
        {
            centerizeRect(levels.numTextures[i].dstrect, winRect);
            levels.x = levels.numTextures[i].dstrect.x;
        }
        else
        {
            SDL_Rect r = {
                levels.numTextures[i-1].dstrect.x, levels.numTextures[i-1].dstrect.y,
                levels.numTextures[i-1].dstrect.w, levels.numTextures[i-1].dstrect.h,
            };
            levels.numTextures[i].dstrect.x += levels.x;
            levels.numTextures[i].dstrect.y += r.y + r.h + LEVEL_VERTICAL_DISTANCE;
        }
    }

    levels.levelTexture = loadFont("level", MENU_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION,
        LEVEL_FONT_SIZE - 40);
    centerizeRect(levels.levelTexture.dstrect, levels.numTextures[levels.cur].dstrect);
    levels.levelTexture.dstrect.x -= levels.levelTexture.dstrect.w / 2;
}

void LevelDestroyLevel(Asteroids& asters)
{
    AsteroidsDestroy(asters);
}

void LevelLoadLevel(Levels& self, Asteroids& asters, Enemy& enemy)
{
    LevelDestroyLevel(asters);

    Level level = self.levels[self.cur];
    AsteroidsInit(asters, level.asters);
    enemy.active = level.enemy;
}

void shiftElements(Levels& self, int side)
{
    int sign;
    switch (side)
    {
    case LEVEL_SHIFT_UP:   sign = -1; break;
    case LEVEL_SHIFT_DOWN: sign = 1;  break;
    }

    int offset = self.numTextures[0].dstrect.h + LEVEL_VERTICAL_DISTANCE;

    for (int i = 0; i < self.num; i++)
        self.numTextures[i].dstrect.y -= sign * offset;
    self.cur += sign;
}

void LevelUpdate(Levels& levels, Asteroids& asters, Enemy& enemy, Keys& keys,
    int& gameState
)
{
    int ticks = SDL_GetTicks();
    if (ticks - levels.ticks < LEVEL_DELAY_BUTTONS) return;
    levels.ticks = ticks;

    if (keys.w || keys.up)
    {
        if (levels.cur == 0) return;
        shiftElements(levels, LEVEL_SHIFT_UP);
    }

    if (keys.s || keys.down)
    {
        if (levels.cur == levels.num - 1) return;
        shiftElements(levels, LEVEL_SHIFT_DOWN);
    }

    if (keys.space || keys.enter)
    {
        LevelLoadFile(LEVEL_FILE_FILENAME);
        LevelLoadLevel(levels, asters, enemy);
        MusicEffectsPlay(MUSIC_BUTTON);
        gameState = GAME_STATE_SOLO;
        levels.inited = false;
    }
}

void LevelDraw(Levels& levels)
{
    for (int i = 0; i < levels.num; i++)
    {
        SDL_Rect rect = levels.numTextures[i].dstrect;
        int alpha = LEVEL_FONT_TRANSPARENT;
        if (i == levels.cur)
        {
            rect.x += 30;
            alpha = 255;
        }
        SDL_SetTextureAlphaMod(levels.numTextures[i].tex, alpha);
        SDL_RenderCopy(ren, levels.numTextures[i].tex, 0, &rect);
    }
    SDL_RenderCopy(ren, levels.levelTexture.tex, 0, &levels.levelTexture.dstrect);
}
