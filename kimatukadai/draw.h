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
void drawPixel(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);// �h�b�g�摜���쐬����֐�
point* setPoint(size* dsize, point *p); // ���W��ݒ肷��֐�
void paintPixel(size* dsize, point* cp, int cnum); // 1�}�X����h�邽�߂̊֐�
void drawCanvas();	// �`��G���A��`��
void drawSuccess(); // �������݂̐���I����\��
void drawMain(int data[16][16], size *dsize, int cnum, int mode, char fileName[CHARBUFF]);	// ���C����ʂ�`�悷��֐�