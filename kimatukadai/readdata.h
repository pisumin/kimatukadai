#pragma once
#define CHARBUFF 128
#include "draw.h"

errno_t CSV2Array(const char* fileName, size *dsize, int data[16][16]); // CSVファイルを配列に格納
int Array2CSV(size* dsize, int data[16][16], char fileName[CHARBUFF], int mode); // 配列をCSVファイルに格納
