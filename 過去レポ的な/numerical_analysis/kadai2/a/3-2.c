#include "NAbasic.h"
#define DX 0.001 /*����*/
#define N 11 /*2���@�̌J��Ԃ���*/

double func(double x){
	return x*x*x*x - 3*x*x + 5*x -9;
}

/*2���@�ɂ���@*/

int main(int argc, char ** argv){

	FILE *fin;
	int row,col,i;
	double **matrix;
	double a1,a2,f1,f2,x,mid;

	/*���͂̊m�F*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s infile\n", argv[0]);
		return EXIT_FAILURE;
	}

	/*�t�@�C���̓ǂݍ���*/
	if((fin  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	matrix = csvRead(&row,&col,fin);

	/*��Ԃ̓ǂݍ���*/

	a1 = matrix[0][0];
	a2 = matrix[0][1];

	f1 = func(a1);

	/*2���@�ŉ����ߎ�*/
	for(i=0;i<=N;i++){
		mid = (a1+a2)/2.0;
		if(func(mid)*func(a1)<0) a2 = mid;
		else a1 = mid;
		printf("%d���:%0.10f\n",i,mid);
	}

	return 0;
}
