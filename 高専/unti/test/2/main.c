#include "NAbasic.h" 

/*
calcMatrix(double **mat1,int row1,int col1, double **mat2, int row2, int col2)
  2�̍s��̐ς��v�Z��2�����z��Ɍ��ʂ��i�[����

  ����
	mat1: ��ڂ̍s��
	row1,col1 : mat1�̍s���Ɨ�
	mat2: ��ڂ̍s��
	row2,col2 : mat2�̍s���Ɨ�
  �o��
	mat3:
*/

double** calcMatrix(double **mat1,int row1,int col1, double **mat2, int row2, int col2){

	int i,j,k;
	double **mat3;
	
	/*�v�Z�\���𔻒�*/
	if(col1 != row2){
		printf("�v�Z�ł��܂���");
		exit(EXIT_FAILURE);
	}

	/*�v�Z���ʊi�[�p�z���p��*/
	mat3 = allocMatrix(row1,col2);

	/*�s����v�Z*/
	for(i=0;i<row1;i++){
		for(j=0;j<col2;j++){
			mat3[i][j]=0;
			for(k=0;k<col1;k++){
				mat3[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}

	return mat3;
}

int main(int argc, char ** argv){

	FILE *fin1,*fin2; 
	double **matrix1,**matrix2,**ans;
	int row1,col1,row2,col2;
	
	if(argc != 3){
		fprintf(stderr,"Usage: %s infile1 infile2 \n", argv[0]);
		return EXIT_FAILURE;
	}

	
	/*1�ڂ̃t�@�C���̓ǂݍ���*/
	if((fin1  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	matrix1 = csvRead(&row1,&col1,fin1);
	
	/*2�ڂ̃t�@�C���̓ǂݍ���*/
	if((fin2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

	matrix2 = csvRead(&row2,&col2,fin2);
	
	/*�s��̐ς��v�Z*/
	ans = calcMatrix(matrix1,row1,col1,matrix2,row2,col2);

	/*���ʂ�\��*/
	showMatrix((const double**)ans, row1 , col2);

	/*�̈�̊J��*/
	freeMatrix(ans);
	freeMatrix(matrix1);
	freeMatrix(matrix2);
	
	return 0;
}
