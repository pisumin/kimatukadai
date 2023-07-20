#include <stdio.h>
#include <curses.h>
#include "readini.h"
#include "readdata.h"

int mode; /* 描画モード 0:新規作成, 1:*/
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
	init_pair(1, COLOR_WHITE, COLOR_BLACK); // デフォルト
	keypad(stdscr, TRUE);

	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);

	/* モードによって挙動を変える */
	/* 新規作成モードならタイトル表示->サイズ選択->描画画面 */
	/* ファイル読み込みならタイトル表示->描画画面 */

	/* 2秒間タイトル画面表示 */
//	drawTitle();
//	napms(2000);

	// 新規作成モード
//	if (mode == 0)
//	{
	// サイズ選択画面
	dsize = modeSelect();
//	}
		// ファイル読み込みモード
	//	else {

	//	}

//	while (1)
//	{
//		erase();
//		mvaddstr(0, 0, "モード選択終了");
//		int key = getch();
//		if (key == 'q') break;
//		refresh();
//	}
	printf("%d, %d\n", dsize->xmax, dsize->ymax);
	return 0;
}