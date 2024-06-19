#include <math.h>
#include "NAbasic.h"

#define BUF 80
#define EPS 1e-8

/*---------------------------------------------------
	�s��ƃx�N�g���̐ς����߂�
	����: (�s��, �x�N�g��, �s��̍s��, �s��̗�, �x�N�g���̎���)
	�߂�l: ��(�x�N�g��)
---------------------------------------------------*/
double* matrix_times_vector(double** x, double* y, int xrow, int xcol, int ylen) {
	int i, j;
	double* ret = allocVector(ylen); // ���ʂ̃x�N�g��

	// ����������Ȃ���΃G���[
	if (xrow != ylen) {
		puts("Defective data! (matrix_times_vector())");
		return ret;
	}

	// �v�Z
	for (i = 0; i < xrow; i++) {
		for (j = 0; j < xcol; j++) {
			ret[i] += x[i][j] * y[j];
		}
	}

	return ret;
}

//�O�i�����̊֐�
void forward_elimination(double** l, double* y, double* pb, int n) {
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


/*---------------------------------------------------
	�s���x�s�ڂ�y�s�ڂ�����
	����: (�s��, �s��̍s��, x, y)
	�߂�l: ����������0, ���s������0�ȊO
---------------------------------------------------*/
int swap_row(double** a, int row, int x, int y) {
	// �s�����͈͊O��������G���[
	if (x < 0 || x >= row || y < 0 || y >= row) {
		puts("Defective Input (swap_row())");
		return EXIT_FAILURE;
	}

	double* tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;

	return EXIT_SUCCESS;
}

/*---------------------------------------------------
	LU����
	����: (A�s��, L�s��, U�s��, P�s��, �s��̍s��)
	�߂�l: ����������0, ���s������0�ȊO
---------------------------------------------------*/
int lu(double** a, double** l, double** u, double** p, int n) {
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

/*---------------------------------------------------
	�x�N�g��x�ƃx�N�g��y�̓��ς����߂�
	����: (x, y, �x�N�g���̎���)
	�߂�l: ����
---------------------------------------------------*/
double inner_product(double* x, double* y, int len) {
	int i;
	double ret = 0;

	for (i = 0; i < len; i++) {
		ret += x[i] * y[i];
	}
	return ret;
}

/*---------------------------------------------------
	�x�N�g����P�ʃx�N�g���ɐ��K������
	����: (�x�N�g��, �x�N�g���̎���)
	�߂�l: ����������0, ���s(0�x�N�g����������)������0�ȊO
---------------------------------------------------*/
int normalize(double* x, int len) {
	double norm = 0; // �x�N�g���̃m����
	int i;

	// �x�N�g���̃m�����v�Z
	for (i = 0; i < len; i++) {
		norm += x[i] * x[i];
	}

	norm = sqrtf(norm);

	if (0 == norm) {
		puts("Defective Input (normalize())");
		return EXIT_FAILURE;
	}

	// �e�v�f���m�����Ŋ����Ă���
	for (i = 0; i < len; i++) {
		x[i] /= norm;
	}

	return EXIT_SUCCESS;
}

int main() {
	FILE* fin;
	double** A, ** L, ** U, ** P, * y, * last_y, * z, lambda = 10e8, last_lambda;
	int i, Arow, Acol;
	char file_name[BUF];

	printf("A CSV File Name<< ");
	scanf("%s", file_name);
	puts("");

	// �t�@�C���ǂݍ���
	if (NULL == (fin = fopen(file_name, "r"))) {
		fprintf(stderr, "The file doesn't exist.\n");
		return EXIT_FAILURE;
	}

	// �t�@�C������s��ǂݍ���
	A = csvRead(&Arow, &Acol, fin);

	// �ϐ��̃������m��
	y = allocVector(Arow);
	last_y = allocVector(Arow);

	// y��K���ȃx�N�g���ɂ��Ƃ�
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

	// y��K���ȃx�N�g���ɂ��Ƃ�
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