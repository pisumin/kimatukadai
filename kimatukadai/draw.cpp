#include <curses.h>
#include <string.h>
#include "draw.h"
#define CHARBUFF 128
/* メイン画面等，画面の描画を行う関数 */

void drawTitle()
{

}

void paintBack()
{
	erase();
	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);
	attrset(COLOR_PAIR(10));
	for (int i = 0;i < h;i++)
	{
		for (int j = 0;j < w;j++)
		{
			mvaddch(i, j, ' ');
		}
	}
	refresh();
}

void drawSelect(){
	attrset(COLOR_PAIR(1));
	erase();
	paintBack();
	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);
	// 座標設定
	const char* select = "描画サイズを選択してください";
	x = (w - strlen(select)) / 2;
	y = h / 3;
	mvaddstr(y, x, select);
	select = "(→キーで次へ)";
	x = (w - strlen(select)) / 2;
	mvaddstr(++y, x, select);

	y = h / 2;
	int size = 4;
	/* 選択できるサイズを表示 */
	for (int i = 0;i < 3; i++)
	{
		char sizes[CHARBUFF];
		sprintf_s(sizes, "%02d × %02d", size, size);
		x = (w - strlen(sizes)) / 2;
		y += h / 8;
		mvaddstr(y, x, sizes);
		size *= 2;
	}
	refresh();
}

size* modeSelect()
{
	size* tmp = new size();
	int x1, y1, h, w;
	getmaxyx(stdscr, h, w);
	// 選択用のカーソルを動かす
	y1 = h / 2 + h / 8;
	x1 = (w - 3*strlen("04 × 04")) / 2 - 2;
	while (1)
	{
		erase();
		drawSelect();
		mvaddstr(y1, x1, "→");
		// スペースでサイズ決定
		int key = getch();

		// →ボタン押下でセレクト終了
		if (key == KEY_RIGHT) break;
		//上下キーでカーソル移動
		switch (key)
		{
		case KEY_UP:
			if (y1 == h / 2 + h / 8) y1 += h / 8 * 2;
			else y1 -= h / 8;
			break;
		case KEY_DOWN:
			if (y1 == h / 2 + (h / 8) * 3) y1 = h / 2 + h / 8;
			else y1 += h / 8;
			break;
		default:
			break;
		}
		refresh();
	}
	// サイズを確定
	if (y1 == h / 2 + h / 8)
	{
		tmp->xmax = 4; tmp->ymax = 4;
	}
	else if (y1 == h / 2 + h / 8 * 2)
	{
		tmp->xmax = 8; tmp->ymax = 8;
	}
	else
	{
		tmp->xmax = 16; tmp->ymax = 16;
	}

	return tmp;
}

void drawPallet()
{
	erase();
	paintBack(); // あとで外す(メインで一気に書くよ！)
	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);
	x = (w + 32) / 2 + 12;
	y = h / 2 - 3;
	for (int i = 1;i < 10;i++)
	{
		attrset(COLOR_PAIR(i));
		for (int j = 0;j < 2;j++)
		{
			// カラー番号を表示
			if (j == 0) mvprintw(y++, x, "%d 　", i);
			else mvaddstr(y, x, "　　");
		}
		if ((i % 3) == 0)
		{
			x = (w + 32) / 2 + 12; y++;
		}
		else
		{
			x += 4; y--;
		}
	}
	refresh();
}

void drawPixel(char data[16][16][CHARBUFF])
{

}

void drawMain()
{

}