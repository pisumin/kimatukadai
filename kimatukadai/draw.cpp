#include <curses.h>
#include <string.h>
#include "draw.h"
#include "readdata.h"
#define CHARBUFF 256

/* メイン画面等，画面の描画を行う */

/* 背景を描画．関数内で呼び出す*/
void paintBack()
{
	// 座標の設定
	point p;
	p.x = 0, p.y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);
	
	// 画面全体を背景色で塗りつぶし
	attrset(COLOR_PAIR(10));
	for (int i = 0;i < h;i++)
	{
		for (int j = 0;j < w;j++)
		{
			mvaddch(i, j, ' ');
		}
	}
}

/* サイズ選択画面の描画．ここでは描画のみ行う．*/
void drawSelect()
{
	// 背景
	paintBack();

	// 座標の設定
	point* p = new point();
	p->x = 0; p->y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);

	attrset(COLOR_PAIR(10));
	const char* info = "ドット絵を作成します";
	p->x = (w - strlen(info)) / 2;
	p->y = h / 4;
	mvaddstr(p->y, p->x, info);
	info = "(ファイルから読み込む場合はiniファイルにファイル名を記述してください)";
	p->x = (w - strlen(info)) / 2 + 1;
	p->y = h / 4 + 1;
	mvaddstr(p->y, p->x, info);
	const char* select = "描画サイズを選択してください";
	p->x = (w - strlen(select)) / 2;
	p->y = h / 3;
	mvaddstr(p->y, p->x, select);
	select = "(↑↓キーで選択、→キーで決定)";
	p->x = (w - strlen(select)) / 2;
	mvaddstr(++p->y, p->x, select);

	// サイズを表示する枠を描画
	p->x = (w - 3 * strlen("04 × 04")) / 2 - 4;
	p->y = h / 2;
	drawFrame(p, 3 * strlen("04 × 04") + 10, h / 2 - 2);

	// 選択できるサイズを描画
	p->y = h / 2;
	int size = 4;
	attrset(COLOR_PAIR(9));
	for (int i = 0;i < 3; i++)
	{
		char sizes[CHARBUFF];
		sprintf_s(sizes, "%02d × %02d", size, size);
		p->x = (w - strlen(sizes)) / 2;
		p->y += h / 8;
		mvaddstr(p->y, p->x, sizes);
		size *= 2;
	}
}

/* サイズの選択画面を描画し，キー操作によってサイズ選択を行う．(メイン関数ではこれを呼び出し)
   選択されたサイズをsize型のポインタとして返す． */
size* modeSelect()
{
	size* tmp = new size();
	point p;
	int h, w;
	getmaxyx(stdscr, h, w);

	// 選択用のカーソル(→)を動かす
	p.y = h / 2 + h / 8;
	p.x = (w - 3*strlen("04 × 04")) / 2 - 2;
	while (1)
	{
		erase();
		// 選択肢の表示
		drawSelect();
		// カーソルの表示
		attrset(COLOR_PAIR(9));
		mvaddstr(p.y, p.x, "→");

		int key = getch();
		// →キー押下でサイズ決定
		if (key == KEY_RIGHT) break;
		// ↑↓キーでカーソル移動
		switch (key)
		{
		case KEY_UP:
			// 一番上にカーソルがあった場合，一番下に移動
			if (p.y == h / 2 + h / 8) p.y += h / 8 * 2;
			else p.y -= h / 8;
			break;
		case KEY_DOWN:
			// 一番下にカーソルがあった場合，一番上に移動
			if (p.y == h / 2 + (h / 8) * 3) p.y = h / 2 + h / 8;
			else p.y += h / 8;
			break;
		default:
			break;
		}
		refresh();
	}
	// サイズが確定→返り値としてサイズを返す
	// 一番上(4*4)
	if (p.y == h / 2 + h / 8)
	{
		tmp->xmax = 4; tmp->ymax = 4;
	}
	// 二番目(8*8)
	else if (p.y == h / 2 + h / 8 * 2)
	{
		tmp->xmax = 8; tmp->ymax = 8;
	}
	// 三番目(16*16)
	else
	{
		tmp->xmax = 16; tmp->ymax = 16;
	}
	return tmp;
}

/* 描画色を選択するためのパレットを描画
   描画する色とその番号(1～9)を表示 */
void drawPallet()
{
	// 座標の設定
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	p.x = (w + 32) / 2 + 12;
	p.y = h / 2 - 2;

	// カラー番号(メイン関数内で設定)1～9まで表示
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
}

/* ドット絵の描画を行う関数 
	data[16][16] : 各マスの色情報を格納する配列．格納される数字は，カラー番号に対応．
					(x, y)=(2,1)がカラー番号3なら，data[1][2]に3が格納される．
	dsize : 描画サイズ
	cnum : カラー番号
	mode : 描画モード．新規作成なら0，ファイルから読み込みなら1
	fileName : 終了時に書き込む対象となるファイルの名前 */
void drawPixel(int data[16][16], size* dsize, int cnum, int mode, char fileName[CHARBUFF])
{
	// 座標の設定
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// キャンバス内の座標を設定 : 4*4ならx座標0～3，y座標0～3とする
	point *cp = new point();
	cp->x = 0, cp->y = 0;
	// キャンバス内の座標を画面全体での座標に変換する．
	p = setPoint(dsize, cp);

	// 選択中のカラーを表示
	point pp;
	pp.x = (w + 32) / 2 + 12;
	pp.y = h / 2 - 4;

	// ファイルから読み込みモードなら，あらかじめdata内にドット絵の情報があるため，それを描画
	if (mode == 1)
	{
		// data内の情報に基づいて色を描画
		for (int i = 0;i < dsize->ymax; i++)
		{
			for (int j = 0;j < dsize->xmax;j++)
			{
				paintPixel(dsize, cp, data[i][j]);
				cp->x++;
			}
			cp->x = 0;
			cp->y++;
		}
	}

	// 今どこにいるかを示す(半角カーソルを表示)
	cp->x = 0; cp->y = 0;
	p = setPoint(dsize, cp);
	attrset(COLOR_PAIR(12));
	mvaddstr(p->y, p->x, " ");
	refresh();
	// カーソル表示の有無(1->有，0->無)
	int curs = 1;

	while (1)
	{
		// 選択中のカラーを表示
		attrset(COLOR_PAIR(10));
		mvprintw(pp.y, pp.x, "選択中のカラー:%d", cnum);

		int key = getch();
		// q押下でファイル書き込みを行って終了
		if (key == 'q')
		{
			// ファイル書き込みが正常終了
			if (Array2CSV(dsize, data, fileName, mode) == 0)
			{
				break;
			}
			// 失敗した場合は，その旨を1秒間表示してアプリを続行
			else {
				char tmp[CHARBUFF] = "書き込みに失敗しました";
				mvaddstr(0, (w-strlen(tmp))/2, tmp);
				refresh();
				napms(1000);
				mvaddstr(0, (w - strlen(tmp)) / 2, "　　　　　　　　　　　");
			}
		}

		switch (key)
		{
		// 描画位置の移動
		case KEY_RIGHT:
			// 右端じゃなければ
			if (cp->x != dsize->xmax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x++;
				p = setPoint(dsize, cp);
				// カーソル表示がONならカーソルを描画
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_LEFT:
			// 左端じゃなければ
			if (cp->x != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x--;
				p = setPoint(dsize, cp);
				// カーソル表示がONならカーソルを描画
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_UP:
			// 一番上じゃなければ
			if (cp->y != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y--;
				p = setPoint(dsize, cp);
				// カーソル表示がONならカーソルを描画
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_DOWN:
			// 一番下じゃなければ
			if (cp->y != dsize->ymax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y++;
				p = setPoint(dsize, cp);
				// カーソル表示がONならカーソルを描画
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		// カラーの変更
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			// 押されたカラーに変更
			cnum = key - '0';
			break;
		// p押下で今いるマスに選択中の色を描画
		case 'p':
			paintPixel(dsize, cp, cnum);
			// data配列の内容を更新
			data[cp->y][cp->x] = cnum;
			// カーソル表示がONならカーソルを描画
			if (curs)
			{
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		// c押下でカーソル表示の切替
		case 'c':
			// カーソル表示ONならOFFにする
			if (curs)
			{
				curs = 0;
				//カーソルを消す
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
			}
			// カーソル表示OFFならONにする
			else
			{
				curs = 1;
				// カーソルを表示
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		default:
			break;
		}
		refresh();
	}
}

/* 座標位置を設定する関数 
	dsize : 描画サイズ．cp : キャンバス内の座標*/
point *setPoint(size* dsize, point *cp)
{
	point* rp = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// 座標変換
	rp->x = (w - 32) / 2 + cp->x * 2 * (16 / dsize->xmax);
	rp->y = (h - 16) / 2 + cp->y * (16 / dsize->ymax);
	return rp;
}

/* 1マス分を描画する関数　
	dsize : 描画サイズ，cp : キャンバス内の座標，cnum : カラー番号*/
void paintPixel(size* dsize, point *cp, int cnum)
{
	point *p = setPoint(dsize, cp);
	int tmp = p->x;
	// 1マスの大きさ分だけその色で半角スペースを描画．x方向は半角で座標+1なので*2する
	for (int i = 0;i < 16 / dsize->ymax;i++)
	{
		for (int j = 0; j < 16 / dsize->xmax * 2; j++)
		{
			attrset(COLOR_PAIR(cnum));
			mvaddstr(p->y, p->x, " ");
			p->x++;
		}
		p->x = tmp;
		p->y++;
	}
}

/* ドット絵を描画するためのキャンバスを描画 */
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
				attrset(COLOR_PAIR(11)); // 茶色
				mvaddstr(p.y, p.x, " ");
			}
			else {
				if (j <= 1 || j >= 34)
				{
					attrset(COLOR_PAIR(11)); // 茶色
					mvaddstr(p.y, p.x, " ");
				}
				else {
					attrset(COLOR_PAIR(9)); // 白色
					mvaddstr(p.y, p.x, " ");
				}
			}
			p.x++;
		}
		p.x = (w - 32) / 2 - 2;
		p.y++;
	}
}

/* 書き込みが正常終了した旨を表示 */
void drawSuccess()
{
	paintBack();
	// 座標の設定
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	char str[CHARBUFF] = "書き込みが終了しました";
	p.x = (w - strlen(str)) / 2;
	p.y = h / 2;
	attrset(COLOR_PAIR(10));
	mvaddstr(p.y, p.x, str);
	refresh();
	// 2秒待機
	napms(2000);
}

/* サイズ選択や操作方法表示などに用いる枠の描画
	sp : 枠(白色部分)の開始位置)，xs : x方向の白色の幅，ys : y方向の白色の幅 */
void drawFrame(point* sp, int xs, int ys)
{
	point* tp = new point();
	tp->x = sp->x - 2; tp->y = sp->y - 1;
	// 枠内を白色で，枠を水色(カーソルと同色)で塗る
	for (int i = 0;i < ys + 2;i++)
	{
		for (int j = 0;j < xs + 2; j++)
		{
			if (i == 0 || i == ys + 1)
			{
				attrset(COLOR_PAIR(12)); // 水色
				mvaddstr(tp->y, tp->x, " ");
			}
			else {
				if (j <= 1 || j >= xs)
				{
					attrset(COLOR_PAIR(12)); // 水色
					mvaddstr(tp->y, tp->x, " ");
				}
				else {
					attrset(COLOR_PAIR(9)); // 白色
					mvaddstr(tp->y, tp->x, " ");
				}
			}
			tp->x++;
		}
		tp->x = sp->x - 2;
		tp->y++;
	}
}

/* 操作方法を表示 */
void drawManual()
{
	// 座標の設定
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// 枠の描画
	p->x = (w - 32) / 2 - 38;
	p->y = h / 2 - 3;
	drawFrame(p, 32, 7);

	// 操作方法を描画
	p->x = (w - 32) / 2 - 36;
	p->y = h / 2 - 2;
	attrset(COLOR_PAIR(9));
	mvaddstr(p->y++, p->x, "矢印キー：描画マスの移動");
	mvaddstr(p->y++, p->x, "数字キー：色の変更");
	mvaddstr(p->y++, p->x, "p 　　　：描画");
	mvaddstr(p->y++, p->x, "c 　　　：カーソル表示切替");
	mvaddstr(p->y, p->x, "q 　　　：終了");
}

/* メイン画面(メイン関数ではこれを呼び出し) */
void drawMain(int data[16][16],size *dsize,int cnum, int mode, char fileName[CHARBUFF])
{
	erase();
	paintBack();	// 背景を描画
	drawPallet();	// パレットを描画
	drawCanvas();	// キャンバスを描画
	drawManual();	// 操作方法を描画
	drawPixel(data, dsize, cnum, mode, fileName);	// 描画を行う
	drawSuccess();	// 書き込みの正常終了を描画
}