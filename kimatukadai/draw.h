#pragma once
#include <stdio.h>
#include <curses.h>
#define CHARBUFF 128

/* 描画サイズによって1マスの大きさを変更 */
/* 行方向は半角で1マス(多分)なので，倍にする */
typedef struct {
	int xmax;
	int ymax;
} size;

void drawTitle();	// タイトルを描画する関数
void paintBack();	// 背景を塗りつぶす
void drawSelect();	// サイズ一覧を描画する関数
size* modeSelect();	// モード選択画面を描画する関数
void drawPallet();	// パレットを描画する関数
void drawPixel(char data[16][16][CHARBUFF]); // ドット画像を作成する関数
void drawMain();	// メイン画面を描画する関数