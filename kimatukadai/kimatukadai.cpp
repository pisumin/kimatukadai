#include <stdio.h>
#include <curses.h>
#include "readini.h"
#include "readdata.h"

int mode; // 描画モード 0:新規作成, 1:ファイルから読み込み
int cnum = 1; // カラー番号
char fileName[CHARBUFF]; // 設定ファイルのファイル名
int data[16][16] = {}; // 16(y方向)×16(x方向)の配列 ファイルから読み込んだ際のデータを格納．描画サイズが未知なので最大にしておく．
size* dsize = new size();

int main()
{
	// 設定ファイルの読み込み
	mode = readIni(fileName);
	if (mode == -1)	return -1;

	initscr(); 		// 端末制御の開始
	noecho();		// 入力された文字を表示しないようにする
	curs_set(0);	// カーソルを表示しない

	// 色の設定
	start_color();
	init_color(8,  1000, 647,  0);	  // オレンジ色
	init_color(9,  1000, 1000, 878);  // 背景色(Light Yellow)
	init_color(10, 1000, 0,    1000); // マゼンタ
	init_color(11, 1000, 1000, 0);	  // 黄色
	init_color(12, 545,  271,  76);   // 茶色(SaddleBrown)
	init_color(13, 1000, 1000, 1000); // 白色(なんかくすんでる気がしたからこっち)
	init_color(14, 0,    1000, 1000); // シアン
	init_color(15, 373,  620,  627);  // CadetBlue

	init_pair(1, COLOR_WHITE, COLOR_BLACK);   // 黒で描画(カラー1)
	init_pair(2, COLOR_WHITE, COLOR_RED);	  // 赤で描画(カラー2)
	init_pair(3, COLOR_WHITE, COLOR_BLUE);	  // 青で描画(カラー3)
	init_pair(4, COLOR_WHITE, COLOR_GREEN);	  // 緑で描画(カラー4)
	init_pair(5, COLOR_BLACK, 14);			  // 水色で描画(カラー5)
	init_pair(6, COLOR_BLACK, 8);			  // オレンジ色で描画(カラー6)
	init_pair(7, COLOR_BLACK, 11);			  // 黄色で描画(カラー7)
	init_pair(8, COLOR_BLACK, 10);			  // ピンク色で描画(カラー8)
	init_pair(9, COLOR_BLACK, 13);			  // 白色で描画(カラー9)
	init_pair(10, COLOR_BLACK, 9);			  // 背景色
	init_pair(11, COLOR_BLACK, 12);			  // キャンバスの縁の色
	init_pair(12, COLOR_WHITE, 15);			  // カーソル用の色

	keypad(stdscr, TRUE);	// キー入力をON

	// モードによって挙動を変える
	// 新規作成モードならサイズ選択->描画画面
	// ファイル読み込みなら描画画面

	// 新規作成モード
	if (mode == 0)
	{
		// 配列を白色(カラー番号9)で初期化
		for (int i = 0; i < 16;i++)
		{
			for (int j = 0;j < 16;j++)
			{
				data[i][j] = 9;
			}
		}
		// サイズ選択画面．選択された描画サイズを受け取る
		dsize = modeSelect();
	}
	// ファイル読み込みモード
	else {
		// データの読み込み(読み込み中にエラーが発生したらそのまま異常終了する)
		if (CSV2Array(fileName, dsize, data) != 0)
			return -1;
	}

	// メイン画面の表示
	drawMain(data, dsize, cnum, mode, fileName);

	return 0;
}