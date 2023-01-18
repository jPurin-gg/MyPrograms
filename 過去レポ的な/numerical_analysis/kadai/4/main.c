#include <math.h>
#include "NAbasic.h"

void get_file_name(char *file_name) {

	printf("CSV File Name<< ");
	scanf("%s", file_name);
	puts("");
}

void swap_row(double **a, int row, int col, int x, int y) {
    if (x < 0 || x >= row || y < 0 || y >= row) {
        puts("Defective Input (swap_row())");
        return;
    }

    double *tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}

void print_mat(double **A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%3.2f", A[i][j]);
		}
		puts("");
	}
}

int main(int argc, char **argv) {
	FILE *fin;
	double **A, **y, maxabs;
	int i, j, k, pivot, Arow, Acol, yrow, ycol;
	char file_name[80];


	if (NULL == (fin = fopen(argv[1], "r"))) {
		fprintf(stderr, ".\n");
		return EXIT_FAILURE;
	}
	A = csvRead(&Arow, &Acol, fin);

	printf("y CSV File Name<< ");
	scanf("%s", file_name);
	puts("");

	if (NULL == (fin = fopen(argv[2], "r"))) {
		fprintf(stderr, "\n");
		return EXIT_FAILURE;
	}
	y = csvRead(&yrow, &ycol, fin);
	
	for (k = 0; k < Arow; k++) {  /* �悋�X�e�b�v */
      	pivot = k;
      	maxabs = fabs(A[k][k]);
      	for (i = k + 1; i < Arow; i++) {  /* �s�{�b�g�I�� */
         	if (fabs(A[i][k]) > maxabs) {
            	pivot = i;
            	maxabs = fabs(A[i][k]);
         	}
      	}

 /* �G���[�����F�s�{�b�g�����܂�ɏ��������̓��b�Z�[�W��\�����ďI���@*/
		if (fabs(maxabs) < 1.0e-12) {
			printf("too small pivot! \n");
			return EXIT_FAILURE;
		}
		swap_row(A, Arow, Acol, pivot, k);
/* �O�i���� */
      for (i = k + 1; i < Arow; i++) { /* �悉�s */
         A[i][k] = 0.0;
         /* �悋�s��-a[i][k]/a[k][k]�{���āA�悉�s�ɉ����� */
         for (j = k + 1; j < Acol; j++){
            A[i][j] = A[i][j] - A[k][j] * A[i][k] / A[k][k];
         }
         y[i] = y[i] - y[k] * A[i][k] / A[k][k];
      }
   }
/* ��ޑ�� */
      for (i = Arow - 1; i >= 0; i--){
         for (j = i + 1; j < Acol; j++){
            y[i] = y[i] - A[i][j] * y[j];
            A[i][j] = 0.0;
         }
         y[i] = y[i] / A[i][i];
         A[i][i] = 1.0;
      }
/* ���̕\�� */

	print_mat(y, Arow, 1);

	return EXIT_SUCCESS;
}