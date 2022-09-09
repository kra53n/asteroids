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
    printf("\nrecord filename: %s", filename);
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

    int* records = 0;
    num = 0;

    while (!feof(f))
    {
        char record[120];
        fscanf_s(f, "%s", record, 120);

        num++;
        records = (int*)realloc(records, sizeof(int) * num);
        records[num-1] = atoi(record);
    }

    return records;
}

int getPosInLevelRecords(int levelNum, int record)
{
    if (!recordFileExist(levelNum))
        return 0;

    int num;
    int* records = readRecordFile(num, levelNum);

    sortNums(records, num, SORTING_BY_DECREMENCE);

    int pos = -1;
    for (int i = 0; i < num; i++)
    {
        printf("\nnum: %d", records[i]);
        if (record < records[i])
            continue;
        pos = i;
        break;
    }

    if (pos < 0)
        pos = num;

    free(records);
    return pos;
}

void writeRecord(int levelNum, int record)
{
    char* filename = getFilename(levelNum);

    FILE* f;
    if (fopen_s(&f, filename, "a"))
    {
        printf("\nError when trying to open file %s in writeRecord function", filename);
        deInit(1);
    }
    free(filename);
    fprintf(f, "%d ", record);
    fclose(f);
}
