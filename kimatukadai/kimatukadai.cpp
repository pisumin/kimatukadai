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
//	printf_s("%s\n", fileName);
//	printf_s("モード=%d\n", mode);

/*	if (mode == 1)
	{
		CSV2Array(fileName, dsize, data);
		printf("%d,%d\n", dsize->xmax, dsize->ymax);
		for (int i = 0;i < dsize->ymax;i++)
		{
			for (int j = 0;j < dsize->xmax; j++) {
				printf("%s, ", data[i][j]);
			}
			printf("\n");
		}
	}
*/

	/* 端末制御の開始 */
//	initscr();

	/* モードによって挙動を変える */
	/* 新規作成モードならタイトル表示->サイズ選択->描画画面 */
	/* ファイル読み込みならタイトル表示->描画画面 */

	/* 2秒間タイトル画面表示 */
//	drawTitle();
//	napms(2000);

//	int key = getch();

//	if (mode == 0)
//	{
//		while (key != 'a')
//		{
			// キー入力を取得
	//		key = getch();
			/* スペースなりエンターなりで決定されるまで表示 */
//			int size = drawSelect();
//		}
//	}

	return 0;
}