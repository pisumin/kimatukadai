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
	// 座標の設定
	point p;
	p.x = 0, p.y = 0;
	int w, h;
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
	paintBack();
	// 座標の設定
	point p;
	p.x = 0; p.y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);
	// 座標設定
	const char* select = "描画サイズを選択してください";
	p.x = (w - strlen(select)) / 2;
	p.y = h / 3;
	mvaddstr(p.y, p.x, select);
	select = "(→キーで次へ)";
	p.x = (w - strlen(select)) / 2;
	mvaddstr(++p.y, p.x, select);

	p.y = h / 2;
	int size = 4;
	/* 選択できるサイズを表示 */
	for (int i = 0;i < 3; i++)
	{
		char sizes[CHARBUFF];
		sprintf_s(sizes, "%02d × %02d", size, size);
		p.x = (w - strlen(sizes)) / 2;
		p.y += h / 8;
		mvaddstr(p.y, p.x, sizes);
		size *= 2;
	}
	refresh();
}

size* modeSelect()
{
	size* tmp = new size();
	point p;
	int h, w;
	getmaxyx(stdscr, h, w);
	// 選択用のカーソルを動かす
	p.y = h / 2 + h / 8;
	p.x = (w - 3*strlen("04 × 04")) / 2 - 2;
	while (1)
	{
		erase();
		drawSelect();
		mvaddstr(p.y, p.x, "→");
		// スペースでサイズ決定
		int key = getch();

		// →ボタン押下でセレクト終了
		if (key == KEY_RIGHT) break;
		//上下キーでカーソル移動
		switch (key)
		{
		case KEY_UP:
			if (p.y == h / 2 + h / 8) p.y += h / 8 * 2;
			else p.y -= h / 8;
			break;
		case KEY_DOWN:
			if (p.y == h / 2 + (h / 8) * 3) p.y = h / 2 + h / 8;
			else p.y += h / 8;
			break;
		default:
			break;
		}
		refresh();
	}
	// サイズを確定
	if (p.y == h / 2 + h / 8)
	{
		tmp->xmax = 4; tmp->ymax = 4;
	}
	else if (p.y == h / 2 + h / 8 * 2)
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
	// 座標の設定
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	p.x = (w + 32) / 2 + 12;
	p.y = h / 2 - 3;
	for (int i = 1;i < 10;i++)
	{
		attrset(COLOR_PAIR(i));
		for (int j = 0;j < 2;j++)
		{
			// カラー番号を表示
			if (j == 0) mvprintw(p.y++, p.x, "%d 　", i);
			else mvaddstr(p.y, p.x, "　　");
		}
		if ((i % 3) == 0)
		{
			p.x = (w + 32) / 2 + 12; p.y++;
		}
		else
		{
			p.x += 4; p.y--;
		}
	}
	refresh();
}

void drawPixel(char data[16][16][CHARBUFF], size* dsize, int cnum)
{
	// 座標の設定
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// キャンバス内の座標を設定
	point *cp = new point();
	cp->x = 0, cp->y = 0;
	p = setPoint(dsize, cp);
	attrset(COLOR_PAIR(12));
	// 今どこにいるかを示す(半角カーソルを表示)
	mvaddstr(p->y, p->x, " ");
	refresh();
	while (1)
	{
		int key = getch();
		switch (key)
		{
		case KEY_RIGHT:
			if (cp->x != dsize->xmax - 1)
			{
				attrset(COLOR_PAIR(9));
				mvaddstr(p->y, p->x, " ");
				cp->x++;
				p = setPoint(dsize, cp);
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		case KEY_LEFT:
			if (cp->x != 0)
			{
				attrset(COLOR_PAIR(9));
				mvaddstr(p->y, p->x, " ");
				cp->x--;
				p = setPoint(dsize, cp);
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		case KEY_UP:
			if (cp->y != 0)
			{
				attrset(COLOR_PAIR(9));
				mvaddstr(p->y, p->x, " ");
				cp->y--;
				p = setPoint(dsize, cp);
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		case KEY_DOWN:
			if (cp->y != dsize->ymax - 1)
			{
				attrset(COLOR_PAIR(9));
				mvaddstr(p->y, p->x, " ");
				cp->y++;
				p = setPoint(dsize, cp);
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		}
		refresh();
	}
}

point *setPoint(size* dsize, point *cp)
{
	point* rp = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	rp->x = (w - 32) / 2 + cp->x * 2 * (16 / dsize->xmax);
	rp->y = (h - 16) / 2 + cp->y * (16 / dsize->ymax);
	return rp;
}

void drawCanvas()
{
	// 座標の設定
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	// 描画枠を白色で，描画枠のまわりを茶色で示す
	p.x = (w - 32) / 2 - 2;
	p.y = (h - 16) / 2 - 1;
	for (int i = 0;i < 18;i++)
	{
		for (int j = 0;j < 36; j++)
		{
			if (i == 0 || i == 17)
			{
				attrset(COLOR_PAIR(11));
				mvaddstr(p.y, p.x, " ");
			}
			else {
				if (j <= 1 || j >= 34)
				{
					attrset(COLOR_PAIR(11));
					mvaddstr(p.y, p.x, " ");
				}
				else {
					attrset(COLOR_PAIR(9));
					mvaddstr(p.y, p.x, " ");
				}
			}
			p.x++;
		}
		p.x = (w - 32) / 2 - 2;
		p.y++;
	}
}

void drawMain(char data[16][16][CHARBUFF],size *dsize,int cnum)
{
	erase();
	paintBack();
	drawPallet();
	drawCanvas();
	while (1)
	{
		drawPixel(data, dsize, cnum);
		refresh();
	}
}