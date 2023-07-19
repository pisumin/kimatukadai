#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdata.h"
#include "draw.h"
#define CHARBUFF 128

void CSV2Array(const char* fileName, size* dsize, char data[16][16][CHARBUFF])
{
	/* �F�̃f�[�^���i�[����z�� */
	/* �Ƃ肠������ԑ傫���T�C�Y�Ŏw�肵�Ă��� */

	FILE* fp;
	errno_t error;
	int ccnt, rcnt; /* �s���A�񐔂̃J�E���g */
	char s[CHARBUFF], delim[] = ",";
	char* p1, * ctk;
	error = fopen_s(&fp, fileName, "r");
	if (error != 0)
	{
		fprintf_s(stderr, "�t�@�C�����J���܂���\n");
	}
	else
	{
		ccnt = 0;
		int datac = 0; // �f�[�^��1������(x����)�̓Y����
		int datar = 0; // �f�[�^��2������(y����)�̓Y����
		while (fgets(s, CHARBUFF, fp) != NULL)
		{
			rcnt = 0;
			p1 = strtok_s(s, delim, &ctk);
			while (p1 != NULL)
			{
				/* 0�s�ڂɂ̓T�C�Y���i�[ */
				if (ccnt == 0)
				{
					if (rcnt == 0) dsize->xmax = atof(p1); /* ����double�₩��int�̂�T���Ă��������� */
					else if (rcnt == 1) dsize->ymax = atof(p1); 
				}
				/* 1�s�ڈȍ~�ɂ̓f�[�^���i�[*/
				else {
					char* tmp = data[rcnt][ccnt - 1];
					if (rcnt < dsize->xmax)
					{
						*tmp = *p1;
					}
				}
				rcnt++;
			}
			ccnt++;
			/* 6�s�ڂ܂ł�ǂݔ�΂� */
/*			if (ccnt > 5)
			{
				rcnt = 0;
				p1 = strtok_s(s, delim, &ctk);
				while (p1 != NULL)
				{
*/					/* 1,4��ڂ̂ݓǂݍ��� */
/*					if (rcnt == 1)
					{
						data[datac][datar][0] = atof(p1);
					}
					else if (rcnt == 4) {
						data[datac][datar++][1] = atof(p1);
					}
					p1 = strtok_s(NULL, delim, &ctk);
					rcnt++;
				}
			}
			// �z��̍s���ړ�
			if (datar == MONTH)
			{
				datac++; datar = 0;
			}
			ccnt++;
			*/
		}
	}
}
