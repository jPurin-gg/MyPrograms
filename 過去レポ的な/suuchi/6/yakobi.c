#include <stdio.h>
#include <math.h>
#include "NAbasic.h"
#define n 10                       //���m���̌�
#define MAX 100                //�J��Ԃ��ő��
#define eps 1.0e-9           //�ŏ��덷���e�͈�

int main()
{

	FILE *fin1, *fin2;
	double **a, **b;

	int i, j, k, l;
	int row1, col1, row2, col2;
	
	double err;
	double pre_x[n] = { 1.0,1.0,1.0 }, x[n];

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
	printf("�x�N�g��b�̃t�@�C��������͂��Ă��������F");
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


	for (k = 0; k < MAX; k++) {
		for (l = 0; l < n; l++) {
			printf("%lf ", pre_x[l]);
		}
		printf("\n");
		err = 0.0;                        //�덷�̃��Z�b�g
		for (i = 0; i < n; i++) {
			x[i] = *b[i];
			for (j = 0; j < n; j++) {
				if (j != i) {
					x[i] -= a[i][j] * pre_x[j];
				}
			}
			x[i] = x[i] / a[i][i];
		}

		/*�e���̌덷�𑫂��A�Â����͎̂Ĕz��xold�ɐV������������*/
		for (i = 0; i < n; i++) {
			err += fabs(pre_x[i] - x[i]);
			pre_x[i] = x[i];
		}

		/*�������킳�ꂽ�덷�����e�͈͓���������
		�v�Z�I���Ƃ��������܂����Ƃ���*/
		if (err < eps) break;
	}

	/*���܂��������o�͂���*/
	for (i = 0; i < n; i++) {
		printf("%8.4f\n", x[i]);
	}

	/*�J��Ԃ��񐔂��ő�񐔂̒l��������
	���m�ȉ������܂��Ă��Ȃ��\����Ȃ̂Œ���*/
	printf("�J��Ԃ��񐔂� %d\n", k + 1);

	return 0;
}
