#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "funcs.h"
#include "record.h"
#include "config.h"
#include "window.h"

char* getFilename(int levelNum)
{
    int len = 32;
    char* filename = (char*)malloc(sizeof(char) * len);
    sprintf_s(filename, len, "%s%d%s", RECORD_FILENAME_PREFIX, levelNum, RECORD_FILENAME_POSTFIX);
    return filename;
}

bool recordFileExist(int levelNum)
{
    char* filename = getFilename(levelNum);

    FILE* f;
    errno_t err = fopen_s(&f, filename, "r");
    free(filename);

    if (!err)
        fclose(f);
    return !err;
}

int* readRecordFile(int& num, int levelNum)
{
    char* filename = getFilename(levelNum);

    FILE* f;
    if (fopen_s(&f, filename, "r"))
    {
        printf("\nError when trying to read file %s in readRecordFile function", filename);
        deInit(1);
    }
    free(filename);

    int* scores = 0;
    num = 0;

    while (!feof(f))
    {
        char score[120];
        fscanf_s(f, "%s", score, 120);

        num++;
        scores = (int*)realloc(scores, sizeof(int) * num);
        scores[num-1] = atoi(score);
    }

    fclose(f);
    return scores;
}

void writeScore(int levelNum, int score)
{
    char* filename = getFilename(levelNum);

    FILE* f;
    if (fopen_s(&f, filename, "a"))
    {
        printf("\nError when trying to open file %s in writeRecord function", filename);
        deInit(1);
    }
    free(filename);
    fprintf(f, "%d\n", score);
    fclose(f);
}

int getPosInLevelRecords(int levelNum, int score)
{
    if (!recordFileExist(levelNum))
        return 0;

    int num;
    int* scores = readRecordFile(num, levelNum);
    sortNums(scores, num, SORTING_BY_DECREMENCE);

    int pos = -1;
    for (int i = 0; i < num; i++)
    {
        if (score < scores[i])
            continue;
        pos = i;
        break;
    }

    if (pos < 0)
        pos = num-1;

    free(scores);
    return pos;
}

// return -1 if record file without records
int getFirstPosInLevelRecords(int levelNum)
{
    if (!recordFileExist(levelNum))
        return 0;

    int num;
    int* records = readRecordFile(num, levelNum);
    sortNums(records, num, SORTING_BY_DECREMENCE);

    int pos = num > 0 ? records[0] : -1;
    free(records);
    return pos;
}

int getBestScore(int levelNum, int curScore)
{
    if (!recordFileExist(levelNum))
        return curScore;

    int pos = getPosInLevelRecords(levelNum, curScore);
    if (pos == 0)
        return curScore;
    return getFirstPosInLevelRecords(levelNum);
}
