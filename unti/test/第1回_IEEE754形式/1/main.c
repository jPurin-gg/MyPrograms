#include "NAbasic.h"

//IEEE754�`���ɕϊ����ďo��
void IEEE754_conversion(char *c)
{
	int i, j, k;

	printf("sEEEEEEE EEEEdddd dddddddd... \n");

	for (i = sizeof(double) - 1; i >= 0; i--)
	{
		for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--)
		{
			k = c[i] & (1 << j);
			printf("%d", k ? 1 : 0);
		}
		printf(" ");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	FILE *fin;
	double **matrix;
	int row, col;

	char c[sizeof(double)];

	//�R�}���h���C���̏���
	if (argc != 2) {
		fprintf(stderr, "�R�}���h���C�����s���ł��D\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "�t�@�C�������݂��܂���D\n");
		return EXIT_FAILURE;
	}

	//csv�t�@�C������f�[�^��ǂݍ���
	matrix = csvRead(&row, &col, fin);

	//1�ڂ̐��l���R�s�[
	memcpy(c, &matrix[0][0], sizeof(double));

	IEEE754_conversion(c);

	return 0;
}