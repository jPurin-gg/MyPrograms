#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define BUF 80
#define EPS 1e-12

//�s��ƃx�N�g���̐ς����߂�
double* matrix_times_vector(double** x, double* y, int xrow, int xcol, int ylen) {
	int i, j;
	double* ret = allocVector(ylen);

	if (xrow != ylen) {
		puts("error at matrix_times_vector()");
		return ret;
	}

	for (i = 0; i < xrow; i++) {
		for (j = 0; j < xcol; j++) {
			ret[i] += x[i][j] * y[j];
		}
	}

	return ret;
}

//�O�i����
void forward_elimination(double** L, double* y, double* Pb, int Arow) {
	int i, j;

	for (i = 0; i < Arow; i++) {
		y[i] = Pb[i] / L[i][i];
		for (j = 0; j < i; j++) {
			y[i] -= y[j] * L[i][j] / L[i][i];
		}
	}
}

//��ޑ��
void backward_substitution(double** U, double* x, double* y, int Arow) {
	int i, j;

	for (i = Arow - 1; i >= 0; i--) {
		x[i] = y[i] / U[i][i];
		for (j = i + 1; j < Arow; j++) {
			x[i] -= x[j] * U[i][j] / U[i][i];
		}
	}
}

//�s���x�s�ڂ�y�s�ڂ����ւ���
void swap_row(double** a, int row, int x, int y) {
	if (x < 0 || x >= row || y < 0 || y >= row) {
		puts("error at swap_row()");
		return;
	}
	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

//LU�������s���֐�
int LU(double** A, double** L, double** U, double** P, int Arow) {
	int i, j, k, pivot;
	double q;

	for (i = 0; i < Arow; i++) {
		for (pivot = j = i; j < Arow; j++) {
			if (fabs(A[j][i]) > fabs(A[pivot][i])) {
				pivot = j;
			}
		}

		swap_row(A, Arow, i, pivot);
		swap_row(L, Arow, i, pivot);
		swap_row(U, Arow, i, pivot);
		swap_row(P, Arow, i, pivot);

		q = A[i][i];

		// LU����s�\�ł���΃G���[
		if (0 == q) {
			puts("error at LU()");;
			return EXIT_FAILURE;
		}
		for (j = i; j < Arow; j++) {
			L[j][i] = A[j][i];
			A[i][j] /= q;
		}

		for (k = i + 1; k < Arow; k++) {
			q = A[k][i];
			for (j = i; j < Arow; j++) {
				A[k][j] -= A[i][j] * q;
			}
		}

		for (j = i; j < Arow; j++) {
			U[i][j] = A[i][j];
		}
	}

	return EXIT_SUCCESS;
}

//�x�N�g���ǂ����̓��ς��v�Z����
double inner_product(double* x, double* y, int n) {
	int i;
	double ret = 0;

	for (i = 0; i < n; i++) {
		ret += x[i] * y[i];
	}
	return ret;
}

//�x�N�g����P�ʃx�N�g���ɂ���
int normalize(double* x, int n) {
	double norm = 0; 
	int i;

	for (i = 0; i < n; i++) {
		norm += x[i] * x[i];
	}

	norm = pow(norm, 0.5);

	//��x�N�g���̎��̓G���[
	if (0 == norm) {
		puts("error at normalize()");
		return EXIT_FAILURE;
	}

	for (i = 0; i < n; i++) {
		x[i] /= norm;
	}

	return EXIT_SUCCESS;
}



int main(int argc, char* argv[]) {

	FILE *fin;
	double **A, **L, **U, **P;
	double *y, *pre_y, *z;
	double lambda = 10e9, pre_lambda;//�����_�ɂ͏[���傫���l�����Ă���
	int row, col;
	int i, j;
	char file_name[256];
	
	// csv�t�@�C���̓���
	printf("�s��̃t�@�C��������͂��Ă��������F");
	scanf("%s", file_name);
	putchar('\n');

	// csv�t�@�C���ǂݍ���
	if ((fin = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	// csv����f�[�^��ǂݍ���
	A = csvRead(&row, &col, fin);


	y     = allocVector(row);
	pre_y = allocVector(row);

	//y��K���ȍs��ɂ���
	for (i = 0; i < row; i++) {
		y[i] = 1;
	}

	do {
		pre_lambda = lambda;
		memcpy(pre_y, y, sizeof(double) * row);

		y = matrix_times_vector(A, pre_y, row, col, row);
		lambda = inner_product(y, y, row) / inner_product(y, pre_y, row);
		normalize(y, row);
		

	} while (fabs((pre_lambda - lambda) / pre_lambda) > EPS);
	
	printf("�ő�ŗL�l = %.10lf\n", lambda);

	//LU����p�̃��������m��
	L = allocMatrix(row, col);
	U = allocMatrix(row, col);
	P = allocMatrix(row, col);
	z = allocVector(row);

	//P��P�ʍs��ɂ���
	for (i = 0; i < row; i++) {
		P[i][i] = 1;
	}

	//LU�����Ŏ��s������I��
	if (LU(A, L, U, P, row)) {
		return 0;
	}

	//y��K���ȍs��ɂ���
	for (i = 0; i < row; i++) {
		y[i] = 1;
	}

	// �ŏ��ŗL�l�����߂�
	do {
		pre_lambda = lambda;
		memcpy(pre_y, y, sizeof(double) * row);

		forward_elimination(L, z, pre_y, row);
		backward_substitution(U, y, z, row);

		lambda = inner_product(y, pre_y, row) / inner_product(y, y, row);

		normalize(y, row);
	} while (fabs((lambda - pre_lambda) / pre_lambda) > EPS);

	printf("�ŏ��ŗL�l = %.10lf\n", lambda);

	//�������̉��
	freeMatrix(A);
	freeMatrix(L);
	freeMatrix(U);
	freeMatrix(P);
	freeVector(z);
	freeVector(pre_y);
	freeVector(y);
	

	return EXIT_SUCCESS;
}