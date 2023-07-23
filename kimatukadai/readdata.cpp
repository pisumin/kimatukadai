#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdata.h"
#include "draw.h"

void CSV2Array(const char* fileName, size* dsize, int data[16][16])
{
	/* 色のデータを格納する配列 */
	/* とりあえず一番大きいサイズで指定しておく */

	FILE* fp;
	errno_t error;
	int rcnt, ccnt; /* 行数、列数のカウント */
	char s[CHARBUFF], delim[] = ",";
	char* p1, * ctk;
	error = fopen_s(&fp, fileName, "r");
	if (error != 0)
	{
		fprintf_s(stderr, "ファイルが開けません\n");
	}
	else
	{
		rcnt = 0;	   // 1行目に設定
		int datar = 0; // データの1次元目(y方向)の添え字 行
		int datac = 0; // データの2次元目(x方向)の添え字 列
		while (fgets(s, CHARBUFF, fp) != NULL)
		{
			ccnt = 0;	// 1列目に設定
			p1 = strtok_s(s, delim, &ctk);
			while (p1 != NULL)
			{
				/* 0行目にはサイズが格納 */
				if (rcnt == 0)
				{
					if (ccnt == 0) dsize->xmax = atoi(p1);		// 1列目はx方向のサイズ
					else if (ccnt == 1) dsize->ymax = atoi(p1);	// 2列目はy方向のサイズ
				}
				/* 1行目以降にはデータが格納*/
				else {
					if (ccnt <= dsize->xmax)
					{
						data[datar][datac++] = atoi(p1);
					}
				}
				p1 = strtok_s(NULL, delim, &ctk);
				// 次の列に移動
				ccnt++;
			}
			// 1行目以降なら(配列操作を行った後)
			if (rcnt!=0)
			{
				datac = 0; datar++;
			}
			// 次の行に移動
			rcnt++;
		}
	}
}
