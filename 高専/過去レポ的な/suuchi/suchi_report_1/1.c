#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

void swap_row(double **a, int row, int col, int x, int y) {
	if (x <= 0 || x > row || y <= 0 || y > row) {
		puts("�͈͊O�̍s���w�肵�Ă��܂�");
		return;
	}
	x--, y--;
	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
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

	puts("\nbefore\n");

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			printf("%f ", matrix[row][col]);
		}
		printf("\n");
	}

	swap_row(matrix, row, col, 1, 3);

	puts("\nafter\n");

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			printf("%f ", matrix[row][col]);
		}
		printf("\n");
	}

	
	free(matrix);

	return EXIT_SUCCESS;
}