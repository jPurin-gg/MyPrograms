/*�j���[�g���@�ɂ��⊮*/
#include "NAbasic.h"

/*
�⊮�������̒l�����߂�֐�
����
  matrix:�v���f�[�^
  row,col:�v���f�[�^�̍s���A��
  size:�⊮�Ɏg�p����f�[�^��
  x:x���W
�o��
  result:x�ł̒l
*/
double N_interpolation(double **matrix,int row,int col,int size,int x){
  int i,j;
  double product,result=0;
  double **table; /*�������\*/
  table = allocMatrix(size,size);

  /*�\���쐬*/
  for(i=0;i<size;i++) table[i][0] = matrix[i][1];

  for(i=1;i<size;i++){
    for(j=0;j<size-i;j++){
      table[j][i] = (table[j+1][i-1]-table[j][i-1])/(matrix[j+i][0]-matrix[j][0]);
    }
  }

  /*�l�����߂�*/
  for(i=0;i<size;i++){
    product = 1;
    for(j=0;j<i;j++){
      product*=x-matrix[j][0];
    }
    result+=product*table[0][i];
  }

  return result;
}

int main(int argc, char ** argv){
  int x;
	FILE *f;
	int row,col;
  double result;
	double **matrix;

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
	matrix = csvRead(&row,&col,f);

	/*���͂��`�F�b�N*/
	if(col != 2){
		fprintf(stderr, "���͂��Ⴂ�܂�\n");
		return 0;
	}

  /*���͂�v��*/
  printf("x�����");
  scanf("%d",&x);

  result = N_interpolation(matrix,row,col,3,x);
  printf("3�_�ŕ⊮==> y = %f\n",result);

  result = N_interpolation(matrix,row,col,4,x);
  printf("4�_�ŕ⊮==> y = %f\n",result);
}
