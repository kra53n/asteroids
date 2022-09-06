#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "level.h"
#include "config.h"
#include "window.h"

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
