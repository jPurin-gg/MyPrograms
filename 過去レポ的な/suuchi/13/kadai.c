#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

//�֐�f(x, y)�̌v�Z���s���֐�
double f(double x, double y) {
	return -x * y + x;
}

//�z�C���@���s���֐�
double Heun(double x_0, double h, double x_fin, double y_0) {
	double k1, k2;
	int i;
	double x = x_0, y = y_0;

	printf("Answer\n");
	for (x = x_0; x <= x_fin;) {

		k1 = h * f(x, y);
		k2 = h * f(x + h, y + k1);
		
		printf("x = %lf, y = %lf\n", x, y);

		x += h;
		y += (k1 + k2) / 2;
	}
	return y;
}

int main(int argc, char* argv[]) {

	FILE *fin;
	char file_name[256];

	double **a;
	int row, col;
	
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
	a = csvRead(&row, &col, fin);

	//�z�C���@���s��
	Heun(a[0][0], a[0][1], a[0][2], a[0][3]);

	//���������
	fclose(fin);
	free(a);

	return EXIT_SUCCESS;
}