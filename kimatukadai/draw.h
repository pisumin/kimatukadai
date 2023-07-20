#pragma once
#include <stdio.h>
#include <curses.h>

/* 描画サイズによって1マスの大きさを変更 */
/* 行方向は半角で1マス(多分)なので，倍にする */
typedef struct {
	int xmax;
	int ymax;
} size;

void drawTitle();
void drawSelect();
size* modeSelect();
void drawMain();