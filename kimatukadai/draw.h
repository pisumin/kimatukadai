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

void drawTitle();	// �^�C�g����`�悷��֐�
void paintBack();	// �w�i��h��Ԃ�
void drawSelect();	// �T�C�Y�ꗗ��`�悷��֐�
size* modeSelect();	// ���[�h�I����ʂ�`�悷��֐�
void drawPallet();	// �p���b�g��`�悷��֐�
void drawPixel(char data[16][16][CHARBUFF]); // �h�b�g�摜���쐬����֐�
void drawMain();	// ���C����ʂ�`�悷��֐�