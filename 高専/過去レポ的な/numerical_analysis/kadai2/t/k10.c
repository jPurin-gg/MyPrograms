#include <math.h>
#include "NAbasic.h"

/* �֐�f(x)�̒�` */
double f(double x){
	return x * x;
}

double integ_tra(double a0, double a1, double a2){
	int k;
	double h, sum;

	/* ���� */
	h = (a2 - a1)/a0;

	sum = f(a1)/2 + f(a2)/2; /* f0,fn�̍������� */

	/* �V�O�}�̍������� */
	for(k=1; k<=a0-1; k++){
		a1 += h;
		sum += f(a1);
	}

	sum = sum * h; /* �������|���� */

	return sum;
}

int main(int argc, char **argv){
	int row, col;
	double a0, a1, a2, sum;
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

	/* ������ */
	a0 = matrix[0][0];
	/* �͈� */
	a1 = matrix[0][1];
	a2 = matrix[0][2];

	sum = integ_tra(a0, a1, a2);

	printf("��`�����ɂ��� : %f", sum);

	freeMatrix(matrix); /* ������ƌ㏈��������B */

	return EXIT_SUCCESS;
}