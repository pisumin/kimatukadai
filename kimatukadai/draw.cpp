#include <curses.h>
#include <string.h>
#include "draw.h"
#define CHARBUFF 128
/* タイトル画面や描画画面の描画を行う関数 */

void drawTitle()
{

}

void drawSelect(){
	erase();
	// 座標の設定
	int x = 0, y = 0, w, h;
	getmaxyx(stdscr, h, w);
	// 座標設定
	const char* select = "描画サイズを選択してください";
	x = (w - strlen(select)) / 2;
	y = h / 4;
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

void drawMain()
{

}