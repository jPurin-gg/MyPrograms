/*4���̃����Q�E�N�b�^�@�ɂ��DE�̉�@*/
#include "NAbasic.h"
#include<math.h>

/*�����������̉E��*/
double F(double x,double y){
  return -x*y + x;
}

/*
DE�̉������߂�֐�
����
  x0:x�̏����l
  h:�X�e�b�v��
  xf:�ŏI�l
  y0:y�̏����l
*/
void solve_DE(double x0,double h,double xf,double y0){
  double x;
  double y[2],k[4];

  y[1] = y0;

  /*�X�e�b�v����\��*/
  printf("STEP:%f\n",h);

  /*4���̃����Q�E�N�b�^�@*/
  for(x=x0;x<=xf;x+=h){
    y[0] = y[1];

    k[0] = h*F(x,y[0]);
    k[1] = h*F(x+h/2,y[0]+k[0]/2);
    k[2] = h*F(x+h/2,y[0]+k[1]/2);
    k[3] = h*F(x+h,y[0]+k[2]);

    y[1] = y[0] + (k[0]+2*k[1]+2*k[2]+k[3])/6;

    printf("x=%f, y=%f\n",x,y[0]);
  }
}

int main(int argc, char ** argv){
	FILE *f;
	int row,col;
	double **input;

	/*�R�}���h���C�������̊m�F*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s file.CSV\n", argv[0]);
		return EXIT_FAILURE;
	}

	/*�s���CSV�t�@�C���̓ǂݍ���*/
	if((f  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}
	input = csvRead(&row,&col,f);

	/*���͂��`�F�b�N*/
	if((col != 4)||(row !=1 )){
		fprintf(stderr, "���͂��Ⴂ�܂�\n");
		return 0;
	}

  /*DE������*/
  solve_DE(input[0][0],input[0][1],input[0][2],input[0][3]);

  /*�̈�̉�@*/
  freeMatrix(input);
  free(f);
}
