#include "NAbasic.h" 
 
int main(void) 
{ 
	FILE *fin; 
	double **matrix; 
	int row, col; 

	char c[sizeof(double)]; 
	int i, j, k; 

/* CSV����Ώۃf�[�^��ǂݍ��� */ 

	if ((fin = fopen("1.csv", "r")) == NULL)
	{
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}
	
	matrix = csvRead(&row,&col,fin);/*�f�[�^���}�g���b�N�X�Ɋi�[*/

	memcpy(c, &matrix[0][0], sizeof(double)); 

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

	return 0; 
}