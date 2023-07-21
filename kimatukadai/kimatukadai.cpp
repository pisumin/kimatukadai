#include <stdio.h>
#include <curses.h>
#include "readini.h"
#include "readdata.h"

int mode; /* 描画モード 0:新規作成, 1:*/
int cnum; /* カラー番号 */
char fileName[CHARBUFF];
char data[16][16][CHARBUFF]; /* 16(y方向)×16(x方向)の文字列配列 ファイルから読み込んだ際のデータを格納 */
size* dsize = new size();

int main()
{
	mode = readIni(fileName);

	// 端末制御の開始
	initscr();

	// カラーの設定
	start_color();
	init_color(8, 1000, 647, 0);	// オレンジ色
	init_color(9, 871, 721, 529);	// 背景色(BurlyWood)
	init_pair(1, COLOR_WHITE, COLOR_BLACK);   // デフォルトカラー(カラー1)
	init_pair(2, COLOR_WHITE, COLOR_RED);	  // 赤で描画(カラー2)
	init_pair(3, COLOR_WHITE, COLOR_BLUE);	  // 青で描画(カラー3)
	init_pair(4, COLOR_WHITE, COLOR_GREEN);	  // 緑で描画(カラー4)
	init_pair(5, COLOR_BLACK, COLOR_CYAN);	  // 水色で描画(カラー5)
	init_pair(6, COLOR_BLACK, 8);			  // オレンジ色で描画(カラー6)
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);  // 黄色で描画(カラー7) // あんまり黄色に見えへん
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA); // 紫色で描画(カラー8) // 紫やねんけどマゼンタじゃないよな
	init_pair(9, COLOR_BLACK, COLOR_WHITE);	  // 白色で描画(カラー9)
	init_pair(10, COLOR_BLACK, 9);			  // 背景色
	keypad(stdscr, TRUE);

	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);

	/* モードによって挙動を変える */
	/* 新規作成モードならサイズ選択->描画画面 */
	/* ファイル読み込みなら描画画面 */

	// 新規作成モード
	if (mode == 0)
	{
	// サイズ選択画面
		dsize = modeSelect();
	}
	// ファイル読み込みモード
	else {
		// データの読み込み
		CSV2Array(fileName, dsize, data);
	}

	// メイン画面の表示
	drawPallet();
	while (1);

/*	printf("%d, %d\n", dsize->xmax, dsize->ymax);
	for (int i = 0; i < dsize->ymax; i++)
	{
		for (int j = 0;j < dsize->xmax;j++)
		{
			printf("%s ", data[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}