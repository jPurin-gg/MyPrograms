#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define STEP 10

//f(x)���v�Z����֐�
double f(double x) {
	return pow(x, 4) - 3 * x * x + 5 * x - 9;
}

//f'(x)���v�Z����֐�
double df(double x) {
	return 4 * pow(x, 3) - 6 * x + 5;
}

double regula_falsi(double a, double b) {

	printf("�͂��݂����@�̎��s����\n");

	double c;
	int i = 0;
	do {
		c = (a * f(b) - b * f(a)) / (f(b) - f(a));
		if (f(c) == 0) { break; }
		if (f(a) * f(c) < 0) { b = c; }
		if (f(a) * f(c) > 0) { a = c; }
		printf("���s��: %2d, x=%.9lf\n", ++i, c);
		if (i == 10)break;
	} while (fabs(f(c)) > 1e-10);
	return c;
}


//�񕪖@���s���֐�
void nibun(double a1,double a2) {

	int i;
	double mid;

	printf("�񕪖@�̎��s����\n");

	for (i = 1; i <= STEP; i++) {

		mid = (a1 + a2) / 2.0;

		printf("���s��: %2d, x=%.9lf\n", i, mid);

		if (0 > f(a1) * f(mid)) {
			a2 = mid;
		}
		else {
			a1 = mid;
		}
	}
}

//�j���[�g���@���s���֐�
void newton(double a1, double a2) {

	int i;
	double x = (a1 + a2) / 2.0;

	printf("�j���[�g���@�̎��s����\n");
	for (i = 1; i <= STEP; i++) {

		x = x - f(x) / df(x);

		printf("���s��: %2d, x=%.9lf\n", i, x);
	}
}

int main(int argc, char* argv[]) {
	FILE* fin;
	double** matrix;
	double a1, a2;
	int row, col;
	char c[sizeof(double)], file_name[256];
	
	// csv�t�@�C���̓���
	printf("�t�@�C��������͂��Ă��������F");
	scanf("%s", file_name);
	putchar('\n');

	// csv�t�@�C���ǂݍ���
	if ((fin = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	// csv����f�[�^��ǂݍ���
	matrix = csvRead(&row, &col, fin);

	// ���l���R�s�[
	a1 = matrix[0][0];
	a2 = matrix[0][1];
	
	//�͂��݂���
	regula_falsi(a1, a2);

	//�񕪖@�̎��s
	nibun(a1, a2);

	putchar('\n');

	//�j���[�g���@�̎��s
	newton(a1, a2);

	
	free(matrix);

	return EXIT_SUCCESS;
}