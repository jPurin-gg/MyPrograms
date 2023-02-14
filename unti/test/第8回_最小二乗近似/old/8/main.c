#include <math.h>
#include "NAbasic.h"

#define BUF 80
#define EPS 1e-8

// �s��ƃx�N�g���̐ς����߂�
double *matrix_times_vector(double **x, double *y, int xrow, int xcol, int ylen) {
	int i, j;
	double *ret = allocVector(ylen);

	if (xrow != ylen) {
		puts("Defective data! (matrix_times_vector())");
		return ret;
	}

	for (i = 0; i < xrow; i++) {
		for (j = 0; j < xcol; j++) {
			ret[i] += x[i][j] * y[j];
		}
	}

	return ret;
}

// �O�i����
void forward_elimination(
	double **L,
	double *y,
	double *Pb,
	int Arow
) {
	int i, j;

	for (i = 0; i < Arow; i++) {
		y[i] = Pb[i] / L[i][i];
		for (j = 0; j < i; j++) {
			y[i] -= y[j] * L[i][j] / L[i][i];
		}
	}
}

// ��ޑ��
void backward_substitution(
	double **U,
	double *x,
	double *y,
	int Arow
) {
	int i, j;

	for (i = Arow - 1; i >= 0; i--) {
		x[i] = y[i] / U[i][i];
		for (j = i + 1; j < Arow; j++) {
			x[i] -= x[j] * U[i][j] / U[i][i];
		}
	}
}

// �s��̍s����
void swap_row(double **a, int row, int x, int y) {
	if (x < 0 || x >= row || y < 0 || y >= row) {
		puts("Defective Input (swap_row())");
		return;
	}

	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

// LU����
int lu(
	double **A,
	double **L,
	double **U,
	double **P,
	int Arow
) {
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
		if (0 == q) {
			puts("Defective A Data!");
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

// �x�N�g���̓��όv�Z
double inner_product(double *x, double *y, int len) {
	int i;
	double ret = 0;

	for (i = 0; i < len; i++) {
		ret += x[i] * y[i];
	}
	return ret;
}

// �x�N�g���̐��K��(�P�ʃx�N�g���ɂ���)
void normalize(double *x, int len) {
	double norm = 0;
	int i;

	for (i = 0; i < len; i++) {
		norm += x[i] * x[i];
	}

	norm = sqrtf(norm);

	for (i = 0; i < len; i++) {
		x[i] /= norm;
	}
}

int main(int argc, char **argv) {
	FILE *fin;
	double **A, **L, **U, **P, *y, *last_y, *z, lambda = 10e8, last_lambda;
	int i, Arow, Acol;
	char file_name[BUF];

	// �t�@�C���ǂݍ���
	if (NULL == (fin = fopen(argv[1], "r"))) {
		fprintf(stderr, "The file doesn't exist.\n");
		return EXIT_FAILURE;
	}

	// �t�@�C������s��ǂݍ���
	A = csvRead(&Arow, &Acol, fin);

	// �ϐ��̃������m�ہA������
	y      = allocVector(Arow);
	last_y = allocVector(Arow);
	for (i = 0; i < Arow; i++) {
		y[i] = 1;
	}

	// �ő�ŗL�l�����߂�
	do {
		memcpy(last_y, y, sizeof(double) * Arow);
		y = matrix_times_vector(A, last_y, Arow, Acol, Arow);
		last_lambda = lambda;
		lambda = inner_product(y, y, Arow) / inner_product(y, last_y, Arow);
		normalize(y, Arow);
	} while (fabs((lambda - last_lambda) / last_lambda) > EPS);

	printf("Max Eigenvalue: %lf\n", lambda);

	// LU����p�̃������m��
	L = allocMatrix(Arow, Acol);
	U = allocMatrix(Arow, Acol);
	P = allocMatrix(Arow, Acol);
	z = allocVector(Arow);
	// P�͒P�ʍs��ɂ��Ă���
	for (i = 0; i < Arow; i++) {
		P[i][i] = 1;
	}

	// LU���������s������I��
	if (lu(A, L, U, P, Arow)) {
		return EXIT_FAILURE;
	}

	for (i = 0; i < Arow; i++) {
		y[i] = 1;
	}

	// �ŏ��ŗL�l�����߂�
	do {
		memcpy(last_y, y, sizeof(double) * Arow);
		forward_elimination(L, z, last_y, Arow);
		backward_substitution(U, y, z, Arow);
		last_lambda = lambda;
		lambda = inner_product(y, last_y, Arow) / inner_product(y, y, Arow);
		normalize(y, Arow);
	} while (fabs((lambda - last_lambda) / last_lambda) > EPS);

	printf("Min Eigenvalue: %lf\n", lambda);

	return EXIT_SUCCESS;
}