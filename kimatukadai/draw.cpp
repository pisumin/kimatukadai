#include <curses.h>
#include <string.h>
#include "draw.h"
#include "readdata.h"
#define CHARBUFF 128

/* ���C����ʓ��C��ʂ̕`����s���֐� */
void paintBack()
{
	// ���W�̐ݒ�
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
}

void drawSelect(){
	paintBack();
	// ���W�̐ݒ�
	point* p = new point();
	p->x = 0; p->y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);

	attrset(COLOR_PAIR(10));
	const char* select = "�`��T�C�Y��I�����Ă�������";
	p->x = (w - strlen(select)) / 2;
	p->y = h / 3;
	mvaddstr(p->y, p->x, select);
	select = "(�����L�[�őI���A���L�[�Ō���)";
	p->x = (w - strlen(select)) / 2;
	mvaddstr(++p->y, p->x, select);

	// �T�C�Y�̕\���g��`��
	p->x = (w - 3 * strlen("04 �~ 04")) / 2 - 4;
	p->y = h / 2;
	drawFrame(p, 3 * strlen("04 �~ 04") + 10, h / 2 - 2);

	p->y = h / 2;
	int size = 4;
	attrset(COLOR_PAIR(9));
	/* �I���ł���T�C�Y��\�� */
	for (int i = 0;i < 3; i++)
	{
		char sizes[CHARBUFF];
		sprintf_s(sizes, "%02d �~ %02d", size, size);
		p->x = (w - strlen(sizes)) / 2;
		p->y += h / 8;
		mvaddstr(p->y, p->x, sizes);
		size *= 2;
	}
}

size* modeSelect()
{
	size* tmp = new size();
	point p;
	int h, w;
	getmaxyx(stdscr, h, w);
	// �I��p�̃J�[�\���𓮂���
	p.y = h / 2 + h / 8;
	p.x = (w - 3*strlen("04 �~ 04")) / 2 - 2;
	while (1)
	{
		erase();
		drawSelect();
		attrset(COLOR_PAIR(9));
		mvaddstr(p.y, p.x, "��");
		// �X�y�[�X�ŃT�C�Y����
		int key = getch();

		// ���{�^�������ŃZ���N�g�I��
		if (key == KEY_RIGHT) break;
		//�㉺�L�[�ŃJ�[�\���ړ�
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
	// �T�C�Y���m��
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
	// ���W�̐ݒ�
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	p.x = (w + 32) / 2 + 12;
	p.y = h / 2 - 2;
	for (int i = 1;i < 10;i++)
	{
		attrset(COLOR_PAIR(i));
		for (int j = 0;j < 2;j++)
		{
			// �J���[�ԍ���\��
			if (j == 0) mvprintw(p.y++, p.x, "%d �@", i);
			else mvaddstr(p.y, p.x, "�@�@");
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

void drawPixel(int data[16][16], size* dsize, int cnum, int mode, char fileName[CHARBUFF])
{
	// ���W�̐ݒ�
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// �L�����o�X���̍��W��ݒ�
	point *cp = new point();
	cp->x = 0, cp->y = 0;
	p = setPoint(dsize, cp);
	// ���݂̃J���[��\��
	point pp;
	pp.x = (w + 32) / 2 + 12;
	pp.y = h / 2 - 4;

	if (mode == 1)
	{
		// data���̏��Ɋ�Â��ĐF��`��
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

	// ���ǂ��ɂ��邩������(���p�J�[�\����\��)
	cp->x = 0; cp->y = 0;
	p = setPoint(dsize, cp);
	attrset(COLOR_PAIR(12));
	mvaddstr(p->y, p->x, " ");
	refresh();
	// �J�[�\���\���̗L��(1->�L�C0->��)
	int curs = 1;

	while (1)
	{
		attrset(COLOR_PAIR(10));
		mvprintw(pp.y, pp.x, "�I�𒆂̃J���[:%d", cnum);

		int key = getch();
		// q�����Ńt�@�C���������݂��s���ďI��
		if (key == 'q')
		{
			if (Array2CSV(dsize, data, fileName, mode) == 0)
			{
				break;
			}
			else {
				char tmp[CHARBUFF] = "�������݂Ɏ��s���܂���";
				mvaddstr(0, (w-strlen(tmp))/2, tmp);
				refresh();
				napms(1000);
				mvaddstr(0, (w - strlen(tmp)) / 2, "�@�@�@�@�@�@�@�@�@�@�@");
			}
		}

		switch (key)
		{
		// �`��ʒu�̈ړ�
		case KEY_RIGHT:
			if (cp->x != dsize->xmax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x++;
				p = setPoint(dsize, cp);
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_LEFT:
			if (cp->x != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x--;
				p = setPoint(dsize, cp);
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_UP:
			if (cp->y != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y--;
				p = setPoint(dsize, cp);
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_DOWN:
			if (cp->y != dsize->ymax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y++;
				p = setPoint(dsize, cp);
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		// �J���[�̕ύX
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			cnum = key - '0';
			break;
		// p�����ł��̐F�ō��w���Ă�}�X�ɕ`��
		case 'p':
			paintPixel(dsize, cp, cnum);
			data[cp->y][cp->x] = cnum;
			break;
		// c�����ŃJ�[�\���\���̐ؑ�
		case 'c':
			// �J�[�\���\���L
			if (curs)
			{
				curs = 0;
				//�J�[�\��������
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
			}
			else
			{
				curs = 1;
				// �J�[�\����\��
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

point *setPoint(size* dsize, point *cp)
{
	point* rp = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	rp->x = (w - 32) / 2 + cp->x * 2 * (16 / dsize->xmax);
	rp->y = (h - 16) / 2 + cp->y * (16 / dsize->ymax);
	return rp;
}

void paintPixel(size* dsize, point *cp, int cnum)
{
	point *p = setPoint(dsize, cp);
	int tmp = p->x;
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

void drawCanvas()
{
	// ���W�̐ݒ�
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	// �`��g�𔒐F�ŁC�`��g�̂܂��𒃐F�Ŏ���
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

void drawSuccess()
{
	paintBack();
	// ���W�̐ݒ�
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	char str[CHARBUFF] = "�������݂��I�����܂���";
	p.x = (w - strlen(str)) / 2;
	p.y = h / 2;
	attrset(COLOR_PAIR(10));
	mvaddstr(p.y, p.x, str);
	refresh();
	napms(2000);
}

void drawFrame(point* sp, int xs, int ys)
{
	point* tp = new point();
	tp->x = sp->x - 2; tp->y = sp->y - 1;
	// �g���𔒐F�ŁC�g�O�𐅐F(�J�[�\���Ɠ��F)�œh��
	for (int i = 0;i < ys + 2;i++)
	{
		for (int j = 0;j < xs + 2; j++)
		{
			if (i == 0 || i == ys + 1)
			{
				attrset(COLOR_PAIR(12));
				mvaddstr(tp->y, tp->x, " ");
			}
			else {
				if (j <= 1 || j >= xs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(tp->y, tp->x, " ");
				}
				else {
					attrset(COLOR_PAIR(9));
					mvaddstr(tp->y, tp->x, " ");
				}
			}
			tp->x++;
		}
		tp->x = sp->x - 2;
		tp->y++;
	}
}

void drawManual()
{
	// ���W�̐ݒ�
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// �`��g�𔒐F�ŁC�`��g�̂܂��𒃐F�Ŏ���
	p->x = (w - 32) / 2 - 38;
	p->y = h / 2 - 3;
	drawFrame(p, 32, 7);

	// ������@��`��
	p->x = (w - 32) / 2 - 36;
	p->y = h / 2 - 2;
	attrset(COLOR_PAIR(9));
	mvaddstr(p->y++, p->x, "���L�[�F�`��}�X�̈ړ�");
	mvaddstr(p->y++, p->x, "�����L�[�F�F�̕ύX");
	mvaddstr(p->y++, p->x, "p �@�@�@�F�`��");
	mvaddstr(p->y++, p->x, "c �@�@�@�F�J�[�\���\���ؑ�");
	mvaddstr(p->y, p->x, "q �@�@�@�F�I��");
}

void drawMain(int data[16][16],size *dsize,int cnum, int mode, char fileName[CHARBUFF])
{
	erase();
	paintBack();
	drawPallet();
	drawCanvas();
	drawManual();
	drawPixel(data, dsize, cnum, mode, fileName);
	drawSuccess();
}