#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdata.h"
#include "draw.h"

errno_t CSV2Array(const char* fileName, size* dsize, int data[16][16])
{
	/* �F�̃f�[�^���i�[����z�� */
	/* �Ƃ肠������ԑ傫���T�C�Y�Ŏw�肵�Ă��� */

	FILE* fp;
	errno_t error;
	int rcnt, ccnt; /* �s���A�񐔂̃J�E���g */
	char s[CHARBUFF], delim[] = ",";
	char* p1, * ctk;
	error = fopen_s(&fp, fileName, "r");
	if (error != 0)
	{
		fprintf_s(stderr, "�t�@�C�����J���܂���\n");
		return error;
	}
	else
	{
		rcnt = 0;	   // 1�s�ڂɐݒ�
		int datar = 0; // �f�[�^��1������(y����)�̓Y���� �s
		int datac = 0; // �f�[�^��2������(x����)�̓Y���� ��
		while (fgets(s, CHARBUFF, fp) != NULL)
		{
			ccnt = 0;	// 1��ڂɐݒ�
			p1 = strtok_s(s, delim, &ctk);
			while (p1 != NULL)
			{
				/* 0�s�ڂɂ̓T�C�Y���i�[ */
				if (rcnt == 0)
				{
					if (ccnt == 0) dsize->xmax = atoi(p1);		// 1��ڂ�x�����̃T�C�Y
					else if (ccnt == 1) dsize->ymax = atoi(p1);	// 2��ڂ�y�����̃T�C�Y
				}
				/* 1�s�ڈȍ~�ɂ̓f�[�^���i�[*/
				else {
					if (ccnt <= dsize->xmax)
					{
						data[datar][datac++] = atoi(p1);
					}
				}
				p1 = strtok_s(NULL, delim, &ctk);
				// ���̗�Ɉړ�
				ccnt++;
			}
			// 1�s�ڈȍ~�Ȃ�(�z�񑀍���s������)
			if (rcnt!=0)
			{
				datac = 0; datar++;
			}
			// ���̍s�Ɉړ�
			rcnt++;
		}
		return error;
	}
}

// �h�b�g�摜�̃f�[�^��ǂݍ���
int Array2CSV(size* dsize, int data[16][16], char fileName[CHARBUFF], int mode)
{
	char newFile[CHARBUFF];
	if (mode)
	{
		char tmp[CHARBUFF];
		strncpy_s(tmp, fileName, strlen(fileName)-4);
		snprintf(newFile, CHARBUFF, "%s_1.csv", tmp);
	}
	else
	{
		sprintf_s(newFile, "pixelData.csv");
	}
	FILE* fp;
	errno_t error;
	error = fopen_s(&fp, newFile, "w");

	if (error != 0) return -1;
	else {
		// �T�C�Y���i�[
		char size_s[CHARBUFF];
		snprintf(size_s, CHARBUFF, "%d,%d\n", dsize->xmax, dsize->ymax);
		fputs(size_s, fp);

		// �J���[�ԍ��̃f�[�^���i�[
		for (int i = 0; i < dsize->ymax; i++)
		{
			for (int j = 0;j < dsize->xmax;j++)
			{
				char cnum_s[CHARBUFF];
				snprintf(cnum_s, CHARBUFF, "%d,", data[i][j]);
				fputs(cnum_s, fp);
			}
			fputs("\n", fp);
		}
		fclose(fp);
	}
	return 0;
}