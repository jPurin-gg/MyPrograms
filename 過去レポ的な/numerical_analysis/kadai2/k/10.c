#include <math.h>
#include "NAbasic.h"

//�֐�fx
double fx(double x){
	return x * x;
}

//��`����  ( ������a0, �ϕ��͈�[a1, a2] )
double trapezoid(double **a){
	double i, h, sum = 0;

	h = (a[0][2] - a[0][1]) / a[0][0];

	for(i = a[0][1] + h; i < a[0][2]; i += h){
		sum += fx(i);
	}

	return (h / 2.0) * (fx(a[0][1]) + fx(a[0][2]) + (2.0 * sum));
}

int main(int argc, char **argv){
	FILE *fin;
	double **a;
	int arow, acol;

	//�R�}���h���C���̏���
	if(argc != 2){
		fprintf(stderr, "�R�}���h���C�����s���ł��D\n");
		return EXIT_FAILURE;
	}

	//a��csv�t�@�C���ǂݍ���
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���D\n");
		return EXIT_FAILURE;
	}

	//csv����f�[�^��ǂݍ���
	a = csvRead(&arow, &acol, fin);

	if (1 != arow) {
		puts("���͂��s�K�ł��D\n");
		return EXIT_FAILURE;
	}

	printf("S = %f\n", trapezoid(a));

	return EXIT_SUCCESS;
}