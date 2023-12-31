#define CHARBUFF 256
#include <stdio.h>
#include <string.h>
#include "Setting.h"

/* 設定ファイルを読み込み．描画モードを返す
	fileName : ファイルから読み込みモードの時に，読み込むファイル名を格納するためのファイル*/
int readIni(char* fileName)
{
	// 設定ファイルを読み込み
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
		if (strcmp(keyValue, "None") == 0)
		{
			return 0; // 新規作成モード
		}
		else {
			char tmp[CHARBUFF];
			sprintf_s(tmp, "%s\\%s", currentDirectory, keyValue);
			strcpy_s(fileName, CHARBUFF, tmp);
			return 1; // ファイルから読み込みモード
		}
	}
	else {
		fprintf(stdout, "設定ファイルの読み込みに失敗しました。\n");
		return -1;
	}
}