#define CHARBUFF 128
#include <stdio.h>
#include <string.h>
#include "Setting.h"

/* �ݒ�t�@�C����ǂݍ��݁D�`�惂�[�h��Ԃ�
	fileName : �t�@�C������ǂݍ��݃��[�h�̎��ɁC�ǂݍ��ރt�@�C�������i�[���邽�߂̃t�@�C��*/
int readIni(char* fileName)
{
	// �ݒ�t�@�C����ǂݍ���
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
			return 0; // �V�K�쐬���[�h
		}
		else {
			char tmp[CHARBUFF];
			sprintf_s(tmp, "%s\\%s", currentDirectory, keyValue);
			strcpy_s(fileName, CHARBUFF, tmp);
			return 1; // �t�@�C������ǂݍ��݃��[�h
		}
	}
	else {
		fprintf(stdout, "�ݒ�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
		return -1;
	}
}