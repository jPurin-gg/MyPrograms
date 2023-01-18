#include <math.h>
#include "NAbasic.h"

//�֐�
#define f(x) (exp(x) - pow(x, 3) + 5*sin(x))

//������K�C�K��l
#define N 4
#define EPS 1e-10

//��`����  ( ������a0, �ϕ��͈�[a1, a2] )
void trapezoid(double a0, double a1, double a2){
	double k, h, sum = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += h){
		sum += f(k);
	}

	printf("T = %f", (h / 2.0) * (f(a1) + f(a2) + (2.0 * sum)));
}

//�V���v�\������
void simpson(double a0, double a1, double a2){
	double k, h, sum1 = 0, sum2 = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += (2 * h)){
		sum1 += f(k);
	}

	for(k = a1 + (2 * h); k < a2; k += (2 * h)){
		sum2 += f(k);
	}

	printf("S = %f", (h / 3.0) * (f(a1) + f(a2) + (4.0 * sum1) + (2.0 * sum2)));
}

//�����o�[�O�@
void romberg(double a1, double a2){
	int i, k, m;
	double h, sum, T[N + 1][N + 1];

	//2^0 = 1�����̑�`����
	h = a2 - a1;
	T[0][0] = h * (f(a1) + f(a2)) / 2;
	
	for(k = 1; k <= N; k++) {
		h /= 2;

		for(i = 1, sum = 0; i <= pow(2, (k - 1)); i++){
			sum += f(a1 + (2 * i - 1) * h);
		}
		T[k][0] = T[k - 1][0] / 2.0 + h * sum;

		for(m = 1; m <= k; m++){
			T[k][m] = T[k][m - 1] + (T[k][m - 1] - T[k - 1][m - 1]) / (pow(4, m) - 1);
			//��������
			if(fabs(T[k][m] - T[k][m - 1]) < EPS) break;
		}

		//��������
		if(fabs(T[k][0] - T[k - 1][0]) < EPS) break;
	}

	printf("�������F%d, �����F%d\n", (int)pow(2, k), (int)pow(2, m));
	printf("R = %f", T[k - 1][m - 1]);

/*���ʂ�\��*/
  puts("Romberg Table");
  for(k=0;k<N;k++){
    for(m=0;m<=k;m++){
      printf("%.10f  ",T[k][m]);
    }
    putchar('\n');
  }

  printf("�ϕ��l%f\n",T[N-1][N-1]);
}

int main(int argc, char **argv){
	FILE *fin;
	double a0, a1, a2;
	double **a;
	int arow, acol;

	//�R�}���h���C���̏���
	if(argc != 2){
		fprintf(stderr, "�R�}���h���C�����s���ł��D\n");
		return EXIT_FAILURE;
	}

	//a��csv�t�@�C���ǂݍ���
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���D\n");
		return EXIT_FAILURE;
	}

	//csv����f�[�^��ǂݍ���
	a = csvRead(&arow, &acol, fin);

	if (1 != arow) {
		puts("���͂��s�K�ł��D\n");
		return EXIT_FAILURE;
	}

/*
	a0 = a[0][0];
	a1 = a[0][1];
	a2 = a[0][2];

	trapezoid(a0, a1, a2);
	simpson(a0, a1, a2);
*/

	a1 = a[0][0];
	a2 = a[0][1];

	romberg(a1, a2);

	return EXIT_SUCCESS;
}