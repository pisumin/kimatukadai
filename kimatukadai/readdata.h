#pragma once
#define CHARBUFF 128
#include "draw.h"

void CSV2Array(const char* fileName, size *dsize, char data[16][16][CHARBUFF]);
