#pragma once

bool recordFileExist(int levelNum);
int getPosInLevelRecords(int levelNum, int record);
void writeRecord(int levelNum, int record);
