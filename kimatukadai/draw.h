#pragma once
#include <stdio.h>
#include <curses.h>
#define CHARBUFF 128

/* 描画サイズ
	xmax : x方向の大きさ(幅)，ymax : y方向の大きさ(高さ) */
typedef struct {
	int xmax;
	int ymax;
} size;

/* (x, y)座標を1つの構造体として管理 
	x : x座標，y : y座標 */
typedef struct {
	int x;
	int y;
} point;

void paintBack();	// 背景を塗りつぶす
void drawSelect();	// サイズ一覧を描画する関数
size* modeSelect();	// モード選択画面を描画する関数
void drawPallet();	// パレットを描画する関数
void drawPixel(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);// ドット画像を作成する関数
point* setPoint(size* dsize, point *p); // 座標を設定する関数
void paintPixel(size* dsize, point* cp, int cnum); // 1マス分を塗るための関数
void drawCanvas();	// 描画エリアを描画
void drawSuccess(); // 書き込みが正常終了した旨を表示
void drawFrame(point* sp, int xs, int ys); // 枠を描画
void drawManual(); // 操作方法を描画
void drawMain(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);	// メイン画面を描画する関数