#include "NAbasic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*���Ղ����*/
#define EPS 1e-10

/*���ϋ��߂�i����Ȃ��Ƃ����m�Ŋ|�Z���đS�����������j*/
double inpro(double **x, double **y, int len)
{
    int i;
    double ans=0;
    for(i = 0; i < len; i++)
    {
		ans += x[i][0] * y[i][0];
	}

    return ans;
}

/*�s��A * �s��x �@A�͔C�ӂ̗�ƍs�@x�͗�x�N�g��
�s��A�̃|�C���^,�s��x�̃|�C���^,���̍s��x_n�̃|�C���^,A�̍s��,A�̗�*/
double** Ax(double **A, double **y, double **y_n, int row, int col)
{
    int i, j;
    for(i = 0; i < row; i++)
    {
        y_n[i][0] = 0;
        for(j = 0; j < col; j++)
        {
        y_n[i][0] += A[i][j] * y[j][0];

        }
        
    }

    return y_n;
}
/*�x�N�g���𐳋K��*/
int normalize(double **x, int len) {
	double norm = 0; // �x�N�g���̃m����
	int i;

	/*norm�����Ƃ߂�*/
	for (i = 0; i < len; i++) {
		norm += x[i][0] * x[i][0];
	}
	norm = sqrtf(norm);

	/*norm�Ŋ���*/
	for (i = 0; i < len; i++) {
		x[i][0] /= norm;
	}

	return EXIT_SUCCESS;
}

/*�s���\������֐�*/
void printmat(double **matrixX,int row, int col)
{
    int i,j;
    for(i = 0; i < row; i++)
    {
    printf("|");
        for(j = 0; j < col; j++)
        {
            printf("%lf  ", matrixX[i][j]);

        }
    printf("|\n");
    }
}

/*�s��̍s�����ւ���*/
int swap_row(double **a, int row, int x, int y) {
	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;

	return EXIT_SUCCESS;
}

/*LU����*/
int lu (double **A, double **L, double **U, double **P, int rowA)
{
	int i, j, k, pivot;
	double q;

	for (i = 0; i < rowA; i++) {
		// �s�{�b�g���o
		for (pivot = j = i; j < rowA; j++) {
			if (fabs(A[j][i]) > fabs(A[pivot][i])) {
				pivot = j;
			}
		}

		// �s�{�b�g�Ɋ�Â��čs����
		swap_row(A, rowA, i, pivot);
		swap_row(L, rowA, i, pivot);
		swap_row(U, rowA, i, pivot);
		swap_row(P, rowA, i, pivot);

		q = A[i][i];
		if (0 == q) {
			// LU����s�\�ł���΃G���[
			puts("Defective A Data!");
			return EXIT_FAILURE;
		}
		for (j = i; j < rowA; j++) {
			L[j][i] = A[j][i];
			A[i][j] /= q;
		}

		for (k = i + 1; k < rowA; k++) {
			q = A[k][i];
			for (j = i; j < rowA; j++) {
				A[k][j] -= A[i][j] * q;
			}
		}

		for (j = i; j < rowA; j++) {
			U[i][j] = A[i][j];
		}
	}

	return EXIT_SUCCESS;
}

/*�O�i����*/
void forward_erase(double **L, double **y, double **Pb, int Arow)
{
	int i, j;
	for (i = 0; i < Arow; i++) {
		y[i][0] = Pb[i][0] / L[i][i];
		for (j = 0; j < i; j++) {
			y[i][0] -= y[j][0] * L[i][j] / L[i][i];
		}
	}
}


/*��ޑ��*/
void backward_erase(double **U, double **x, double **y, int Arow)
{
	int i, j;
	for (i = Arow - 1; i >= 0; i--) {
		x[i][0] = y[i][0] / U[i][i];
		for (j = i + 1; j < Arow; j++) {
			x[i][0] -= x[j][0] * U[i][j] / U[i][i];
		}
	}
}

/*main*/
int main (int argc, char** argv)
{
    FILE *finA;
	double **matrixA, **y, **y_next, **L, **U, **P, **z;
    double lambda = 1, last_lambda;
	int rowA, colA, i;


    /*  CSV����Ώۃf�[�^��ǂݍ��� */
	if (((finA = fopen(argv[1], "r")) == NULL))
	{
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

    /*�ǂݍ���CSV�t�@�C�����s��A�ɓ����*/
    matrixA = csvRead(&rowA, &colA, finA);

    /*�ǂݍ���CSV�t�@�C���̍s����o��*/
    printf("A=\n");
    printmat(matrixA,rowA,colA);

    /*��x�N�g��y�����A�K���Ȓl������(�����ł�1)�s��A�̍s�܂��͗�̐����(����������)*/
	y = allocMatrix(rowA,1);
    y_next = allocMatrix(rowA,1);

	for (i = 0; i < rowA; i++)
    {
		y[i][0] = 1;
	}

    /*�ő�ŗL�l�����߂�*/
    while((fabs(lambda - last_lambda) / fabs(last_lambda)) >= EPS){
        last_lambda = lambda;
        y_next = Ax(matrixA,y,y_next,rowA,colA);
        lambda = inpro(y_next, y_next, rowA) / inpro(y_next,y,rowA);

        normalize(y_next, rowA);

        for(i = 0; i < rowA; ++ i)
        {
           y[i][0] = y_next[i][0];
        }
    }

    printf("�ő�ŗL�l: %lf\n", lambda);
    
    /*LU����p�̃������m��*/
	L = allocMatrix(rowA, colA);
	U = allocMatrix(rowA, colA);
	P = allocMatrix(rowA, colA);
	z = allocMatrix(rowA, colA);

	/*�Ƃ肠����P�͒P�ʍs��ɂ���*/
	for (i = 0; i < rowA; i++) {
		P[i][i] = 1;
	}

	/*��x�N�g��y�����A�K���Ȓl������(�����ł�1)�s��A�̍s�܂��͗�̐����(����������)*/
	for (i = 0; i < rowA; i++) {
		y[i][0] = 1;
	}

    /*�s��A��LU��������*/
	if (lu(matrixA, L, U, P, rowA)) {
		return EXIT_FAILURE;
	}
    /*while�̏����������悤�ɒl����Ƃ�
    do while�ł悩��������*/
    lambda = 100000 ;
    last_lambda = 1;

    /*�ŏ��ŗL�l�����߂�*/
    while((fabs(lambda - last_lambda) / fabs(last_lambda)) >= EPS){
        last_lambda = lambda;
        forward_erase(L, z, y, rowA);
        backward_erase(U, y_next, z, rowA);
        lambda = inpro(y_next, y, rowA) / inpro(y_next,y_next,rowA);
        normalize(y_next, rowA);
        for(i = 0; i < rowA; ++ i)
        {
           y[i][0] = y_next[i][0];
        }
    }

    printf("�ŏ��ŗL�l: %lf\n", lambda);

    /*�������΂��΂�*/
    freeMatrix(matrixA);
    freeMatrix(y);
    freeMatrix(y_next);
    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);
    freeMatrix(z);
    return EXIT_SUCCESS;
}