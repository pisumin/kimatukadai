#include <curses.h>
#include <string.h>
#include "draw.h"
#include "readdata.h"
#define CHARBUFF 256

/* ���C����ʓ��C��ʂ̕`����s�� */

/* �w�i��`��D�֐����ŌĂяo��*/
void paintBack()
{
	// ���W�̐ݒ�
	point p;
	p.x = 0, p.y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);
	
	// ��ʑS�̂�w�i�F�œh��Ԃ�
	attrset(COLOR_PAIR(10));
	for (int i = 0;i < h;i++)
	{
		for (int j = 0;j < w;j++)
		{
			mvaddch(i, j, ' ');
		}
	}
}

/* �T�C�Y�I����ʂ̕`��D�����ł͕`��̂ݍs���D*/
void drawSelect()
{
	// �w�i
	paintBack();

	// ���W�̐ݒ�
	point* p = new point();
	p->x = 0; p->y = 0;
	int w, h;
	getmaxyx(stdscr, h, w);

	attrset(COLOR_PAIR(10));
	const char* info = "�h�b�g�G���쐬���܂�";
	p->x = (w - strlen(info)) / 2;
	p->y = h / 4;
	mvaddstr(p->y, p->x, info);
	info = "(�t�@�C������ǂݍ��ޏꍇ��ini�t�@�C���Ƀt�@�C�������L�q���Ă�������)";
	p->x = (w - strlen(info)) / 2 + 1;
	p->y = h / 4 + 1;
	mvaddstr(p->y, p->x, info);
	const char* select = "�`��T�C�Y��I�����Ă�������";
	p->x = (w - strlen(select)) / 2;
	p->y = h / 3;
	mvaddstr(p->y, p->x, select);
	select = "(�����L�[�őI���A���L�[�Ō���)";
	p->x = (w - strlen(select)) / 2;
	mvaddstr(++p->y, p->x, select);

	// �T�C�Y��\������g��`��
	p->x = (w - 3 * strlen("04 �~ 04")) / 2 - 4;
	p->y = h / 2;
	drawFrame(p, 3 * strlen("04 �~ 04") + 10, h / 2 - 2);

	// �I���ł���T�C�Y��`��
	p->y = h / 2;
	int size = 4;
	attrset(COLOR_PAIR(9));
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

/* �T�C�Y�̑I����ʂ�`�悵�C�L�[����ɂ���ăT�C�Y�I�����s���D(���C���֐��ł͂�����Ăяo��)
   �I�����ꂽ�T�C�Y��size�^�̃|�C���^�Ƃ��ĕԂ��D */
size* modeSelect()
{
	size* tmp = new size();
	point p;
	int h, w;
	getmaxyx(stdscr, h, w);

	// �I��p�̃J�[�\��(��)�𓮂���
	p.y = h / 2 + h / 8;
	p.x = (w - 3*strlen("04 �~ 04")) / 2 - 2;
	while (1)
	{
		erase();
		// �I�����̕\��
		drawSelect();
		// �J�[�\���̕\��
		attrset(COLOR_PAIR(9));
		mvaddstr(p.y, p.x, "��");

		int key = getch();
		// ���L�[�����ŃT�C�Y����
		if (key == KEY_RIGHT) break;
		// �����L�[�ŃJ�[�\���ړ�
		switch (key)
		{
		case KEY_UP:
			// ��ԏ�ɃJ�[�\�����������ꍇ�C��ԉ��Ɉړ�
			if (p.y == h / 2 + h / 8) p.y += h / 8 * 2;
			else p.y -= h / 8;
			break;
		case KEY_DOWN:
			// ��ԉ��ɃJ�[�\�����������ꍇ�C��ԏ�Ɉړ�
			if (p.y == h / 2 + (h / 8) * 3) p.y = h / 2 + h / 8;
			else p.y += h / 8;
			break;
		default:
			break;
		}
		refresh();
	}
	// �T�C�Y���m�聨�Ԃ�l�Ƃ��ăT�C�Y��Ԃ�
	// ��ԏ�(4*4)
	if (p.y == h / 2 + h / 8)
	{
		tmp->xmax = 4; tmp->ymax = 4;
	}
	// ��Ԗ�(8*8)
	else if (p.y == h / 2 + h / 8 * 2)
	{
		tmp->xmax = 8; tmp->ymax = 8;
	}
	// �O�Ԗ�(16*16)
	else
	{
		tmp->xmax = 16; tmp->ymax = 16;
	}
	return tmp;
}

/* �`��F��I�����邽�߂̃p���b�g��`��
   �`�悷��F�Ƃ��̔ԍ�(1�`9)��\�� */
void drawPallet()
{
	// ���W�̐ݒ�
	point p;
	int w, h;
	getmaxyx(stdscr, h, w);
	p.x = (w + 32) / 2 + 12;
	p.y = h / 2 - 2;

	// �J���[�ԍ�(���C���֐����Őݒ�)1�`9�܂ŕ\��
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

/* �h�b�g�G�̕`����s���֐� 
	data[16][16] : �e�}�X�̐F�����i�[����z��D�i�[����鐔���́C�J���[�ԍ��ɑΉ��D
					(x, y)=(2,1)���J���[�ԍ�3�Ȃ�Cdata[1][2]��3���i�[�����D
	dsize : �`��T�C�Y
	cnum : �J���[�ԍ�
	mode : �`�惂�[�h�D�V�K�쐬�Ȃ�0�C�t�@�C������ǂݍ��݂Ȃ�1
	fileName : �I�����ɏ������ޑΏۂƂȂ�t�@�C���̖��O */
void drawPixel(int data[16][16], size* dsize, int cnum, int mode, char fileName[CHARBUFF])
{
	// ���W�̐ݒ�
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// �L�����o�X���̍��W��ݒ� : 4*4�Ȃ�x���W0�`3�Cy���W0�`3�Ƃ���
	point *cp = new point();
	cp->x = 0, cp->y = 0;
	// �L�����o�X���̍��W����ʑS�̂ł̍��W�ɕϊ�����D
	p = setPoint(dsize, cp);

	// �I�𒆂̃J���[��\��
	point pp;
	pp.x = (w + 32) / 2 + 12;
	pp.y = h / 2 - 4;

	// �t�@�C������ǂݍ��݃��[�h�Ȃ�C���炩����data���Ƀh�b�g�G�̏�񂪂��邽�߁C�����`��
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
		// �I�𒆂̃J���[��\��
		attrset(COLOR_PAIR(10));
		mvprintw(pp.y, pp.x, "�I�𒆂̃J���[:%d", cnum);

		int key = getch();
		// q�����Ńt�@�C���������݂��s���ďI��
		if (key == 'q')
		{
			// �t�@�C���������݂�����I��
			if (Array2CSV(dsize, data, fileName, mode) == 0)
			{
				break;
			}
			// ���s�����ꍇ�́C���̎|��1�b�ԕ\�����ăA�v���𑱍s
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
			// �E�[����Ȃ����
			if (cp->x != dsize->xmax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x++;
				p = setPoint(dsize, cp);
				// �J�[�\���\����ON�Ȃ�J�[�\����`��
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_LEFT:
			// ���[����Ȃ����
			if (cp->x != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->x--;
				p = setPoint(dsize, cp);
				// �J�[�\���\����ON�Ȃ�J�[�\����`��
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_UP:
			// ��ԏザ��Ȃ����
			if (cp->y != 0)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y--;
				p = setPoint(dsize, cp);
				// �J�[�\���\����ON�Ȃ�J�[�\����`��
				if (curs)
				{
					attrset(COLOR_PAIR(12));
					mvaddstr(p->y, p->x, " ");
				}
			}
			break;
		case KEY_DOWN:
			// ��ԉ�����Ȃ����
			if (cp->y != dsize->ymax - 1)
			{
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
				cp->y++;
				p = setPoint(dsize, cp);
				// �J�[�\���\����ON�Ȃ�J�[�\����`��
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
			// �����ꂽ�J���[�ɕύX
			cnum = key - '0';
			break;
		// p�����ō�����}�X�ɑI�𒆂̐F��`��
		case 'p':
			paintPixel(dsize, cp, cnum);
			// data�z��̓��e���X�V
			data[cp->y][cp->x] = cnum;
			// �J�[�\���\����ON�Ȃ�J�[�\����`��
			if (curs)
			{
				attrset(COLOR_PAIR(12));
				mvaddstr(p->y, p->x, " ");
			}
			break;
		// c�����ŃJ�[�\���\���̐ؑ�
		case 'c':
			// �J�[�\���\��ON�Ȃ�OFF�ɂ���
			if (curs)
			{
				curs = 0;
				//�J�[�\��������
				attrset(COLOR_PAIR((long)data[cp->y][cp->x]));
				mvaddstr(p->y, p->x, " ");
			}
			// �J�[�\���\��OFF�Ȃ�ON�ɂ���
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

/* ���W�ʒu��ݒ肷��֐� 
	dsize : �`��T�C�Y�Dcp : �L�����o�X���̍��W*/
point *setPoint(size* dsize, point *cp)
{
	point* rp = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// ���W�ϊ�
	rp->x = (w - 32) / 2 + cp->x * 2 * (16 / dsize->xmax);
	rp->y = (h - 16) / 2 + cp->y * (16 / dsize->ymax);
	return rp;
}

/* 1�}�X����`�悷��֐��@
	dsize : �`��T�C�Y�Ccp : �L�����o�X���̍��W�Ccnum : �J���[�ԍ�*/
void paintPixel(size* dsize, point *cp, int cnum)
{
	point *p = setPoint(dsize, cp);
	int tmp = p->x;
	// 1�}�X�̑傫�����������̐F�Ŕ��p�X�y�[�X��`��Dx�����͔��p�ō��W+1�Ȃ̂�*2����
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

/* �h�b�g�G��`�悷�邽�߂̃L�����o�X��`�� */
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
				attrset(COLOR_PAIR(11)); // ���F
				mvaddstr(p.y, p.x, " ");
			}
			else {
				if (j <= 1 || j >= 34)
				{
					attrset(COLOR_PAIR(11)); // ���F
					mvaddstr(p.y, p.x, " ");
				}
				else {
					attrset(COLOR_PAIR(9)); // ���F
					mvaddstr(p.y, p.x, " ");
				}
			}
			p.x++;
		}
		p.x = (w - 32) / 2 - 2;
		p.y++;
	}
}

/* �������݂�����I�������|��\�� */
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
	// 2�b�ҋ@
	napms(2000);
}

/* �T�C�Y�I���⑀����@�\���Ȃǂɗp����g�̕`��
	sp : �g(���F����)�̊J�n�ʒu)�Cxs : x�����̔��F�̕��Cys : y�����̔��F�̕� */
void drawFrame(point* sp, int xs, int ys)
{
	point* tp = new point();
	tp->x = sp->x - 2; tp->y = sp->y - 1;
	// �g���𔒐F�ŁC�g�𐅐F(�J�[�\���Ɠ��F)�œh��
	for (int i = 0;i < ys + 2;i++)
	{
		for (int j = 0;j < xs + 2; j++)
		{
			if (i == 0 || i == ys + 1)
			{
				attrset(COLOR_PAIR(12)); // ���F
				mvaddstr(tp->y, tp->x, " ");
			}
			else {
				if (j <= 1 || j >= xs)
				{
					attrset(COLOR_PAIR(12)); // ���F
					mvaddstr(tp->y, tp->x, " ");
				}
				else {
					attrset(COLOR_PAIR(9)); // ���F
					mvaddstr(tp->y, tp->x, " ");
				}
			}
			tp->x++;
		}
		tp->x = sp->x - 2;
		tp->y++;
	}
}

/* ������@��\�� */
void drawManual()
{
	// ���W�̐ݒ�
	point* p = new point();
	int w, h;
	getmaxyx(stdscr, h, w);
	// �g�̕`��
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

/* ���C�����(���C���֐��ł͂�����Ăяo��) */
void drawMain(int data[16][16],size *dsize,int cnum, int mode, char fileName[CHARBUFF])
{
	erase();
	paintBack();	// �w�i��`��
	drawPallet();	// �p���b�g��`��
	drawCanvas();	// �L�����o�X��`��
	drawManual();	// ������@��`��
	drawPixel(data, dsize, cnum, mode, fileName);	// �`����s��
	drawSuccess();	// �������݂̐���I����`��
}