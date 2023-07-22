#pragma once
#include <stdio.h>
#include <curses.h>
#define CHARBUFF 128

/* �`��T�C�Y�ɂ����1�}�X�̑傫����ύX */
/* �s�����͔��p��1�}�X(����)�Ȃ̂ŁC�{�ɂ��� */
typedef struct {
	int xmax;
	int ymax;
} size;

typedef struct {
	int x;
	int y;
} point;

void drawTitle();	// �^�C�g����`�悷��֐�
void paintBack();	// �w�i��h��Ԃ�
void drawSelect();	// �T�C�Y�ꗗ��`�悷��֐�
size* modeSelect();	// ���[�h�I����ʂ�`�悷��֐�
void drawPallet();	// �p���b�g��`�悷��֐�
void drawPixel(char data[16][16][CHARBUFF], size *dsize, int cmode);// �h�b�g�摜���쐬����֐�
point* setPoint(size* dsize, point *p); // ���W��ݒ肷��֐�
void drawCanvas();	// �`��G���A��`��
void drawMain(char data[16][16][CHARBUFF], size *dsize, int cnum);	// ���C����ʂ�`�悷��֐�