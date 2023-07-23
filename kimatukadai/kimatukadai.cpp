#include <stdio.h>
#include <curses.h>
#include "readini.h"
#include "readdata.h"

int mode; /* 描画モード 0:新規作成, 1:*/
int cnum = 1; /* カラー番号 */
char fileName[CHARBUFF];
int data[16][16] = {}; /* 16(y方向)×16(x方向)の文字列配列 ファイルから読み込んだ際のデータを格納 */
size* dsize = new size();

int main()
{
	mode = readIni(fileName);

	// 端末制御の開始
	initscr();
	// 入力された文字を表示しないようにする
	noecho();
	// カーソルを表示しない
	curs_set(0);

	// カラーの設定
	start_color();
	init_color(8,  1000, 647,  0);	  // オレンジ色
	init_color(9,  871,  721,  529);  // 背景色(BurlyWood)
	init_color(10, 1000, 0,    1000); // マゼンタ
	init_color(11, 1000, 1000, 0);	  // 黄色
	init_color(12, 545,  271,  76);   // 茶色(SaddleBrown)
	init_color(13, 1000, 1000, 1000); // 白色(なんかくすんでる気がしたからこっち使う)
	init_color(14, 0,    1000, 1000); // シアン
	init_color(15, 373,  620,  627);  // CadetBlue

	init_pair(1, COLOR_WHITE, COLOR_BLACK);   // 黒で描画(カラー1)
	init_pair(2, COLOR_WHITE, COLOR_RED);	  // 赤で描画(カラー2)
	init_pair(3, COLOR_WHITE, COLOR_BLUE);	  // 青で描画(カラー3)
	init_pair(4, COLOR_WHITE, COLOR_GREEN);	  // 緑で描画(カラー4)
	init_pair(5, COLOR_BLACK, 14);			  // 水色で描画(カラー5)
	init_pair(6, COLOR_BLACK, 8);			  // オレンジ色で描画(カラー6)
	init_pair(7, COLOR_BLACK, 11);			  // 黄色で描画(カラー7)
	init_pair(8, COLOR_BLACK, 10);			  // 紫色で描画(カラー8)
	init_pair(9, COLOR_BLACK, 13);			  // 白色で描画(カラー9)
	init_pair(10, COLOR_BLACK, 9);			  // 背景色
	init_pair(11, COLOR_BLACK, 12);			  // キャンバスの縁の色
	init_pair(12, COLOR_WHITE, 15);			  // カーソル用の色
	keypad(stdscr, TRUE);

	/* モードによって挙動を変える */
	/* 新規作成モードならサイズ選択->描画画面 */
	/* ファイル読み込みなら描画画面 */

	// 新規作成モード
	if (mode == 0)
	{
		// 配列を白色で初期化
		for (int i = 0; i < 16;i++)
		{
			for (int j = 0;j < 16;j++)
			{
				data[i][j] = 9;
			}
		}
	// サイズ選択画面
		dsize = modeSelect();
	}
	// ファイル読み込みモード
	else {
		// データの読み込み(読み込み中にエラーが発生したらそのまま終了する)
		if (CSV2Array(fileName, dsize, data) != 0)
			return -1;
	}

	// メイン画面の表示
	drawMain(data, dsize, cnum, mode, fileName);

	printf_s("ファイルへの書き込みが終了しました．\n");

	return 0;
}