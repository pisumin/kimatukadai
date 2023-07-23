#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdata.h"
#include "draw.h"

void CSV2Array(const char* fileName, size* dsize, int data[16][16])
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
	}
}
