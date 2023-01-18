#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

//�x�N�g�����o�͂���֐�
void printVector(double* a, int row) {
	int i;
	for (i = 0; i < row; i++) {
		printf("%lf ", a[i]);
	}
	putchar('\n');
}

//�s����o�͂���֐�
void printMatrix(double** a, int row, int col) {
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%lf ", a[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

//�s����������֐�
void swap_row(double** a, int row, int x, int y) {
	if (x < 0 || x >= row || y < 0 || y >= row) {
		puts("�͈͊O�̍s���w�肵�Ă��܂�");
		return;
	}
	//x--, y--;
	double* tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

//�s��ƃx�N�g���̐ς��v�Z����֐�
double* matrix_vector_product(double** a, int a_row, int a_col,
	double* b, int b_row) {

	double* res = allocVector(b_row);
	int i, j, k;

	if (a_col != b_row) {
		puts("���Z�ł��܂���");
		return res;
	}

	for (i = 0; i < a_row; i++) {
		for (k = 0; k < a_col; k++) {
			res[i] += a[i][k] * b[k];
		}
	}
	return res;
}

//LU�������s���֐�
int LU(double** a, double** l, double** u, double** p, int n) {
	int i, j, k, pivot;
	double q;

	for (i = 0; i < n; i++) {
		pivot = i;
		for (j = i + 1; j < n; j++) {
			if (fabs(a[j][i]) > fabs(a[pivot][i])) {
				pivot = j;
			}
		}
		swap_row(a, n, i, pivot);
		swap_row(l, n, i, pivot);
		swap_row(u, n, i, pivot);
		swap_row(p, n, i, pivot);

		q = a[i][i];
		if (0 == q) {
			puts("error");
			return EXIT_FAILURE;
		}
		for (j = i; j < n; j++) {
			l[j][i] = a[j][i];
			l[j][i] /= q;
		}
		for (j = i; j < n; j++) {
			u[i][j] = a[i][j];
		}
		for (k = i + 1; k < n; k++) {
			q = l[k][i];
			for (j = i; j < n; j++) {
				a[k][j] -= a[i][j] * q;
			}
		}
	}
	return EXIT_SUCCESS;
}

//�O�i�����̊֐�
void forward_elimination(double **l, double *y, double *pb,int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		y[i] = pb[i] / l[i][i];
		for (j = 0; j < i; j++) {
			y[i] -= y[j] * l[i][j] / l[i][i];
		}
	}
}

//��ޑ���̊֐�
void backward_substitution(double** u, double* x, double* y, int n) {
	int i, j;
	for (i = n - 1; i >= 0; i--) {
		x[i] = y[i] / u[i][i];
		for (j = i + 1; j < n; j++) {
			x[i] -= x[j] * u[i][j] / u[i][i];
		}
	}
}

void solve(double** a, double** l, double** u, double** p, double* b,
			double* pb, double* x, double* y, int row_a, int col_a, int row_b, int col_b) {

	pb = matrix_vector_product(p, row_a, col_a, b, row_b);

	//�O�i�������s��
	forward_elimination(l, y, pb, row_a);

	//��ޑ�����s��
	backward_substitution(u, x, y, row_a);

	//�����o��
	puts("x");
	printVector(x, row_a);
}

int main(int argc, char* argv[]) {

	FILE *fin1, *fin2;
	double **a, **l, **u, **p, **b;
	double *x, *y, *pb;
	int row1, col1, row2, col2;
	int i, j;
	char c[sizeof(double)], file_name1[256], file_name2[256];
	
	// �W���s��csv�t�@�C���̓���
	printf("�W���s��̃t�@�C��������͂��Ă��������F");
	scanf("%s", file_name1);
	putchar('\n');

	// csv�t�@�C���ǂݍ���
	if ((fin1 = fopen(file_name1, "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	// �x�N�g��ycsv�t�@�C���̓���
	printf("�x�N�g��y�̃t�@�C��������͂��Ă��������F");
	scanf("%s", file_name2);
	putchar('\n');

	// csv�t�@�C���ǂݍ���
	if ((fin2 = fopen(file_name2, "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	// csv����f�[�^��ǂݍ���
	a = csvRead(&row1, &col1, fin1);
	b = csvRead(&row2, &col2, fin2);

	//�e�s��E�x�N�g���̃��������m��
	l = allocMatrix(row1, col1);
	u = allocMatrix(row1, col1);
	p = allocMatrix(row1, col1);
	x = allocVector(row1);
	y = allocVector(row1);
	pb = allocVector(row1);

	//p�s���P�ʍs��ɂ���
	for (i = 0; i < row1; i++) p[i][i] = 1;
	
	//LU�������s��
	LU(a, l, u, p, row1);

	//�e�s����o��
	puts("L�s��F");
	printMatrix(l, row1, col1);

	puts("U�s��F");
	printMatrix(u, row1, col1);

	puts("P�s��F");
	printMatrix(p, row1, col1);

	//�A��������������
	solve(a, l, u, p, matrix2colVector(b, row2, col2), pb, x, y, row1, col1, row2, col2);
	
	//��������@������
	freeMatrix(a);
	freeMatrix(l);
	freeMatrix(u);
	freeMatrix(p);
	freeMatrix(b);
	freeVector(x);
	freeVector(y);
	freeVector(pb);


	return EXIT_SUCCESS;
}