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

typedef struct {
	int x;
	int y;
} point;

void drawTitle();	// タイトルを描画する関数
void paintBack();	// 背景を塗りつぶす
void drawSelect();	// サイズ一覧を描画する関数
size* modeSelect();	// モード選択画面を描画する関数
void drawPallet();	// パレットを描画する関数
void drawPixel(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);// ドット画像を作成する関数
point* setPoint(size* dsize, point *p); // 座標を設定する関数
void paintPixel(size* dsize, point* cp, int cnum); // 1マス分を塗るための関数
void drawCanvas();	// 描画エリアを描画
void drawSuccess(); // 書き込みの正常終了を表示
void drawMain(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);	// メイン画面を描画する関数