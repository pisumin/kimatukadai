#define CHARBUFF 128
#include <stdio.h>
#include <string.h>
#include "Setting.h"

int readIni(char* fileName)
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
		if (strcmp(keyValue, "None") == 0)
		{
			return 0; /* 新規作成モード */
		}
		else {
			char tmp[CHARBUFF];
			sprintf_s(tmp, "%s\\%s", currentDirectory, keyValue);
			strcpy_s(fileName, CHARBUFF, tmp);
			return 1; /* ファイルから読み込み */
		}
	}
	else {
		fprintf(stdout, "設定ファイルの読み込みに失敗しました。\n");
		return -1;
	}
}