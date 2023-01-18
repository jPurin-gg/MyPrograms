#include "NAbasic.h"
#define DX 0.001 /*����*/
#define N 10 /*2���@�̌J��Ԃ���*/

double func(double x){
	return x*x*x*x - 3*x*x + 5*x -9;
}

double Dfunc(double x){
	return 4*x*x*x - 6*x + 5;
}

/*�j���[�g���@�ɂ���@*/

int main(int argc, char ** argv){

	FILE *fin;
	int row,col,i;
	double **matrix;
	double a1,a2,x;

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

	x = (a1+a2)/2.0;

	for(i=0;i<N;i++){
		printf("%d���:%.20f\n",i+1,x);
		x = x - func(x)/Dfunc(x);
	}

	return 0;
}
