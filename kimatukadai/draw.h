#pragma once
#include <stdio.h>
#include <curses.h>

/* �`��T�C�Y�ɂ����1�}�X�̑傫����ύX */
/* �s�����͔��p��1�}�X(����)�Ȃ̂ŁC�{�ɂ��� */
typedef struct {
	int xmax;
	int ymax;
} size;

void drawTitle();
void drawSelect();
size* modeSelect();
void drawMain();