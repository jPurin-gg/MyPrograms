#include "NAbasic.h"

// �֐�
double fxy(double x, double y) {
	return (-x * y + x);
}

// �z�C���@
void heun_mh(double x0, double st, double xe, double y0) {
	double x, y;

	printf("STEP:%lf\nAnswer\n", st);
	printf("x=%lf, y=%lf\n", x0, y0);

	while (x < xe) {
		x += st;
		y = y0 + st / 2.0 * (fxy(x0, y0) + (-x * (y0 + st * fxy(x0, y0)) + x));
		printf("x=%lf, y=%lf\n", x, y);
		x0 += st;
		y0 = y;
	}
}

int main(void) {
	FILE *fp;
	double **data;
	double x0, st, xe, y0;
	int row, col;
	char file_name[256];

	// CSV����Ώۃf�[�^��ǂݍ���
	printf("csv�t�@�C������͂��Ă�������:");
	scanf("%s", file_name);
	putchar('\n');
	if((fp = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	data = csvRead(&row, &col, fp);

	// �e�l���
	x0 = data[0][0];	// x�̏����l
	st = data[0][1];	// �X�e�b�v��
	xe = data[0][2];	// x�̍ŏI�l
	y0 = data[0][3];	// y�̏����l

	// �z�C���@
	heun_mh(x0, st, xe, y0);
	
	// �t�@�C��, �������J��
	fclose(fp);
	freeMatrix(data);

	return 0;
}