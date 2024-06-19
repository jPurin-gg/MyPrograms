#include <math.h>
#include "NAbasic.h"

// �֐�f
double f(double x) {
	return (pow(x, 4)) - (3 * pow(x, 2)) + (5 * x) - 9;
}

// ���������֐�df
double df(double x) {
	return (4 * pow(x, 3)) - (6 * x) + 5;
}

// 2���@
void Bisection(
	double a1,
	double a2,
	double (*f)(double x)
){
	int i;
	double mid;

	puts("2���@");

	for (i = 1; 10 >= i; ++i) {
		//��ԗ��[����J�n
		mid = (a1 + a2) / 2.0;

		printf("%2d: x=%.9f\n", i, mid);

		//f(a1)��f(���Ԓl)�̕������ׁCa1�܂���a2�̒l�𒆊Ԓl�ɕς���
		if (0 > f(a1) * f(mid)) {
			a2 = mid;
		} else {
			a1 = mid;
		}
	}
}

// �j���[�g���@
void Newton(
	double a1,
	double a2,
	double(*f)(double x),
	double(*df)(double x)
) {
	int i;
	double x = (a1 + a2) / 2.0;

	puts("�j���[�g���@");

	for (i = 1; 10 >= i; ++i) {
		x = x - (f(x) / df(x));

		printf("%2d: x=%.9f\n", i, x);
	}
}

int main(int argc, char **argv) {
	FILE *fin;
	double **matrix, a1, a2;
	int row, col;

	//�R�}���h���C���̏���
	if (argc != 2) {
		fprintf(stderr, "�R�}���h���C�����s���ł��D\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���D\n");
		return EXIT_FAILURE;
	}

	// csv����f�[�^��ǂݍ���
	matrix = csvRead(&row, &col, fin);

	// �͈͂�������
	a1 = matrix[0][0];
	a2 = matrix[0][1];

	// 2���@
	Bisection(a1, a2, f);
	puts("");

	// �j���[�g���@
	Newton(a1, a2, f, df);

	return EXIT_SUCCESS;
}