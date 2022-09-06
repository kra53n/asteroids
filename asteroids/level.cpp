#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL.h>

#include "menu.h"
#include "funcs.h"
#include "level.h"
#include "config.h"
#include "window.h"
#include "texture.h"

LevelState readState(LevelState state, char const* string);
LevelState processState(LevelState state, const char* string, Level& level);

Levels LevelLoadFile(const char* filename)
{
    FILE* f;
    if (fopen_s(&f, filename, "r"))
    {
        printf("\nError while trying to read file with filename: %s", filename);
        deInit(1);
    }

    Levels levels;
    Level level = { 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0 };

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
        state = processState(state, string, level);

        if (state == LEVEL_STATE)
        {
            levels.num++;
            levels.levels = (Level*)realloc(levels.levels, sizeof(Level) * levels.num);
            levels.levels[levels.num-1] = level;
            level = { 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0 };
        }
    }

    fclose(f);

    return levels;
}

LevelState readState(LevelState state, char const* string)
{
    if      (!strcmp(string, "level"))      return LEVEL_NUM;
    else if (!strcmp(string, "asteroids"))  return LEVEL_ASTEROIDS;
    else if (!strcmp(string, "enemy"))      return LEVEL_ENEMY;
    else if (!strcmp(string, "background")) return LEVEL_BACKGROUND;
    else if (!strcmp(string, "rectord"))    return LEVEL_RECORD;
    return state;
}

void processNumState(const char* string, Level& level);
void processAsteroidsState(const char* string, Level& level);
void processEnemyState(const char* string, Level& level);
void processBackgroundState(const char* string, Level& level);

LevelState processState(LevelState state, const char* string, Level& level)
{
    switch (state)
    {
    case LEVEL_NUM:        processNumState(string, level);        break;
    case LEVEL_ASTEROIDS:  processAsteroidsState(string, level);  break;
    case LEVEL_ENEMY:      processEnemyState(string, level);      break;
    case LEVEL_BACKGROUND: processBackgroundState(string, level); break;
    }
    if (state == LEVEL_BACKGROUND)
        return LEVEL_STATE;
    return state;
}

void processNumState(const char* string, Level& level)
{
    level.num = atoi(string);
}

void processAsteroidsState(const char* string, Level& level)
{
    if (level.asters[ASTEROIDS_TYPE_NUM-1])
        return;

    for (int i = 0; i < ASTEROIDS_TYPE_NUM; i++)
    {
        if (level.asters[i])
            continue;
        level.asters[i] = atoi(string);
        break;
    }
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

    levels.textures = (Texture*)malloc(sizeof(Texture) * levels.num);

    for (int i = 0; i < levels.num; i++)
    {
        char num[4];
        sprintf_s(num, "%d", levels.levels[i].num, 3);

        levels.textures[i] = loadFont(num, MENU_FONTNAME,
            COLOR_OF_NON_ACTIVE_OPTION, LEVEL_FONT_SIZE);

        if (i == 0)
        {
            centerizeRect(levels.textures[i].dstrect, winRect);
            levels.x = levels.textures[i].dstrect.x;
        }
        else
        {
            SDL_Rect r = {
				levels.textures[i-1].dstrect.x, levels.textures[i-1].dstrect.y,
				levels.textures[i-1].dstrect.w, levels.textures[i-1].dstrect.h,
            };
            levels.textures[i].dstrect.x += levels.x;
            levels.textures[i].dstrect.y += r.y + r.h + LEVEL_VERTICAL_DISTANCE;
        }
    }
}

void LevelDestroy(Levels& levels)
{

}

void shiftElements(Levels& self, int side)
{
    int sign;
    switch (side)
    {
    case LEVEL_SHIFT_UP:  sign = -1; break;
    case LEVEL_SHIFT_DOWN: sign = 1;  break;
    }

    int offset = self.textures[0].dstrect.h + LEVEL_VERTICAL_DISTANCE;

    for (int i = 0; i < self.num; i++)
        self.textures[i].dstrect.y -= sign * offset;
    self.cur += sign;
}

void LevelUpdate(Levels& levels, Keys& keys)
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
}

void LevelDraw(Levels& levels)
{
    for (int i = 0; i < levels.num; i++)
    {
        SDL_Rect rect = levels.textures[i].dstrect;
        if (i == levels.cur)
            rect.x += 30;
        SDL_RenderCopy(ren, levels.textures[i].tex, 0, &rect);
    }
}
