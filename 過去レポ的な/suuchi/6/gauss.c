#include <stdio.h>
#include <math.h>
#include "NAbasic.h"
#define n 10                       //���m���̌�
#define MAX 100                //�J��Ԃ��ő��
#define eps 1.0e-9           //�ŏ��덷���e�͈�
#define EPS 1.0e-9           //�ŏ��덷���e�͈�

int main()
{

	FILE *fin1, *fin2;
	double **a, **b;

	int i, j, k, l;
	int row1, col1, row2, col2;
	double dx, absx, sum, new;

	double err;
	double x[n];
	for (i = 0; i < n; i++) {
		x[i] = 0;
	}

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

	do {                                // �����v�Z�̃��[�v
		dx = 0.0;
		absx = 0.0;
		
		for (i = 0; i < n; i++) {
		    sum = 0;
			for (j = 0; j < n; j++) {
				if (i != j) {
					sum += a[i][j] * x[j];
				}
			}
			new = 1.0 / a[i][i] * (b[i][0] - sum);   // �����v�Z��̋ߎ���
			dx += fabs(new - x[i]);           // �ߎ����̕ω��ʂ����Z
			absx += fabs(new);              // �ߎ����̑��a�v�Z
			x[i] = new;                     // �V�����ߎ�������
		}
	} while (dx / absx > EPS);

	/*���܂��������o�͂���*/
	for (i = 0; i < n; i++) {
		printf("%8.4f\n", x[i]);
	}

	/*�J��Ԃ��񐔂��ő�񐔂̒l��������
	���m�ȉ������܂��Ă��Ȃ��\����Ȃ̂Œ���*/
	//printf("�J��Ԃ��񐔂� %d\n", k + 1);

	return 0;
}
