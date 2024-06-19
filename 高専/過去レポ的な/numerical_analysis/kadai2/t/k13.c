#include <math.h>
#include "NAbasic.h"

#define eps 1e-6

/* �֐�f(x)�̒�` */
double divf(double x, double y){
	return -x*y + x;
}

/* �z�����@ */
double horun(double x, double y, double h, double b){
	double y_1;
	while(x < b){
	y_1 = divf(x, y);
	y = y + h/2*(y_1 + divf((x + h), (y + h*y_1)));
	x += h;
	}
	
	return y;
}

int main(int argc, char **argv){
	int row, col;
	double x, y, h, b, s;
	double **matrix;
	FILE *fin;

	/* �K�؂ȃR�}���h���C���������^�����Ă��Ȃ��Ƃ��Ɍx������B */
	if(argc != 2){
		fprintf(stderr, "Usage: %s difficult\n", argv[0]);
		return EXIT_FAILURE;
	}
	if((fin = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "File: %s cannot open\n", argv[1]);
		return EXIT_FAILURE;
	}

	matrix = csvRead(&row, &col, fin); /* �f�[�^�ǂݍ��� */

	x = matrix[0][0];	/* x�̏����l */
	h  = matrix[0][1];	/* �X�e�b�v�� */
	b  = matrix[0][2];	/* x�̍ŏI�l */
	y = matrix[0][3];	/* y�̍ŏI�l */
	
	/* �z�����@ */
	s = horun(x, y, h, b);
		
	printf("�z�����@�ɂ�錋��:%4f", s);
	freeMatrix(matrix);	/* ������ƌ㏈������B */

	return EXIT_SUCCESS;
}