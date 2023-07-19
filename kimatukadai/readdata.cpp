#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdata.h"
#include "draw.h"
#define CHARBUFF 128

void CSV2Array(const char* fileName, size* dsize, char data[16][16][CHARBUFF])
{
	/* 色のデータを格納する配列 */
	/* とりあえず一番大きいサイズで指定しておく */

	FILE* fp;
	errno_t error;
	int ccnt, rcnt; /* 行数、列数のカウント */
	char s[CHARBUFF], delim[] = ",";
	char* p1, * ctk;
	error = fopen_s(&fp, fileName, "r");
	if (error != 0)
	{
		fprintf_s(stderr, "ファイルが開けません\n");
	}
	else
	{
		ccnt = 0;
		int datac = 0; // データの1次元目(x方向)の添え字
		int datar = 0; // データの2次元目(y方向)の添え字
		while (fgets(s, CHARBUFF, fp) != NULL)
		{
			rcnt = 0;
			p1 = strtok_s(s, delim, &ctk);
			while (p1 != NULL)
			{
				/* 0行目にはサイズが格納 */
				if (ccnt == 0)
				{
					if (rcnt == 0) dsize->xmax = atof(p1); /* これdoubleやからintのやつ探してもいいかも */
					else if (rcnt == 1) dsize->ymax = atof(p1); 
				}
				/* 1行目以降にはデータが格納*/
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
			/* 6行目までを読み飛ばす */
/*			if (ccnt > 5)
			{
				rcnt = 0;
				p1 = strtok_s(s, delim, &ctk);
				while (p1 != NULL)
				{
*/					/* 1,4列目のみ読み込む */
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
			// 配列の行を移動
			if (datar == MONTH)
			{
				datac++; datar = 0;
			}
			ccnt++;
			*/
		}
	}
}
