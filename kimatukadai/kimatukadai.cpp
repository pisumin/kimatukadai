#include <stdio.h>
#include <curses.h>
#include "Setting.h"
#include "readdata.h"

int mode; /* 描画モード 0:新規作成, 1:*/
char* fileName;

int main()
{
	/* 設定ファイルを読み込み */
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);

	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "keyword1");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char keyValue[CHARBUFF];

	if (readChar(section, keyWord, "null", keyValue, settingFile))
	{
		if (keyValue == "None")
		{
			mode = 0; /* 新規作成モード */
		} 
		else {
			mode = 1; /* ファイルから読み込み */
			fileName = keyValue;
		}
	}
	else {
		fprintf(stdout, "設定ファイルの読み込みに失敗しました。\n");
	}

	/* 端末制御の開始 */
	initscr();

	/* モードによって挙動を変える */
	/* 新規作成モードならタイトル表示->サイズ選択->描画画面 */
	/* ファイル読み込みならタイトル表示->描画画面 */

	/* 2秒間タイトル画面表示 */
	drawTitle();
	napms(2000);

	int key = getch();

	if (mode == 0)
	{
		while (key != 'a')
		{
			// キー入力を取得
			key = getch();
			/* スペースなりエンターなりで決定されるまで表示 */
			int size = drawSelect();
		}
	}

	return 0;
}