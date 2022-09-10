#pragma once

bool recordFileExist(int levelNum);
void writeScore(int levelNum, int record);

int getPosInLevelRecords(int levelNum, int record);
int getFirstPosInLevelRecords(int levelNum);
int getBestScore(int levelNum, int curScore);
