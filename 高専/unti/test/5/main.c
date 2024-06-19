/*LU������p�����A���ꎟ�������̒��ډ�@*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*��Βl�֐�*/

/*�x�N�g���̗v�f��\������֐�*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

/*�s�̓���ւ�*/
void swap(double **matrix,int row,int i,int pivot){
  double *tmp_vec = matrix[pivot];

  if(!(((0<=i)&&(i<row))&&((0<=pivot)&&(pivot<row)))){
    fprintf(stderr, "�s�̌����Ɏ��s���܂���\n");
    exit(EXIT_FAILURE);
  }

  matrix[pivot] = matrix[i];
  matrix[i] = tmp_vec;
}

/*�s��ƃx�N�g���̐ς��v�Z*/
double *matrix_times_vector(double **A,double *b,int row,int col,int len){
  int i,j;
  double *Ab = allocVector(len);

  if(col != len){
    fprintf(stderr, "�s��ƃx�N�g���̐ς̌v�Z�Ɏ��s���܂���\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
          Ab[i] += A[i][j] * b[j];
      }
  }

  return Ab;
}

/*LU����*/
void LU_decomposition(
  double **A,
  double **L,
  double **U,
  double **P,
  int size
){
  int i,j,k,pivot;
  double tmp,a;

  for(i=0;i<size;i++){
    /*�s�|�b�g��I��*/
		pivot = i;
    for(j=i;j<size;j++){
			if(ABS(A[j][i]) > ABS(A[pivot][i])){
				pivot = j;
			}
		}
    /*A,P�̍s�̓���ւ�*/
    swap(A,size,i,pivot);
    swap(P,size,i,pivot);

    /*L�̌v�Z�������������ւ���*/
    for(j=0;j<i;j++){
      tmp = L[pivot][j];
      L[pivot][j] = L[i][j];
      L[i][j] = tmp;
    }

    for(j = i + 1;j<size;j++){

      if(ABS(A[i][i]) < 1.0e-6){
        fprintf(stderr, "LU�����Ɏ��s\n");
        exit(EXIT_FAILURE);
      }

      L[j][i] = A[j][i]/A[i][i];
      /*�O�i����*/
      a = A[j][i]/A[i][i];
  		for(k=i;k<size;k++){
        A[j][k] -= a*A[i][k];
  		}
    }

    /*U���X�V*/
    for(j=i;j<size;j++){
      U[i][j] = A[i][j];
    }
  }
}

/*�O�i���*/
void foward(double **L,double *y,double *Pb,int size){
  int i,j;

  for(i=0;i<size;i++){
    y[i] = Pb[i]/L[i][i];
    for(j=0;j<i;j++){
      y[i] -= y[j]*L[i][j]/L[i][i];
    }
  }
}

/*��ޑ��*/
void backward(double **U,double *x,double *y,int size){
  int i,j;

  for(i=size-1;i>=0;i--){
    x[i] = y[i]/U[i][i];
    for(j=i+1;j<size;j++){
      x[i] -= x[j]*U[i][j]/U[i][i];
    }
  }
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int Arow,Acol,brow,bcol,i;
	double **A,**matrix,**L,**U,**P;
	double *b,*Pb,*y,*x;

	/*�R�}���h���C�������̊m�F*/
	if(argc != 3){
		fprintf(stderr,"Usage: %s matrix_CSV vector_CSV \n", argv[0]);
		return EXIT_FAILURE;
	}

	/*�s���CSV�t�@�C���̓ǂݍ���*/
	if((f1  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}
	A = csvRead(&Arow,&Acol,f1);

	/*�x�N�g����CSV�t�@�C���̓ǂݍ���*/
	if((f2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}
	matrix = csvRead(&brow,&bcol,f2);

	/*�x�N�g���ɒ���*/
	if(bcol != 1){
		fprintf(stderr, "�x�N�g�������͂���Ă��܂���.\n");
		return EXIT_FAILURE;
	}else{
		b = matrix2colVector(matrix,brow,bcol);
	}

	/*�A���ꎟ�������ƂȂ邩�m�F*/
	if((Acol != brow) && (Acol != Arow)){
		fprintf(stderr, "�A���ꎟ�������ƂȂ�܂���.\n");
		return EXIT_FAILURE;
	}

  /*L,U,P�̍s���p��*/
  L = allocMatrix(Arow,Acol);
  U = allocMatrix(Arow,Acol);
  P = allocMatrix(Arow,Acol);

  /*L,P��P�ʍs��ɂ���*/
  for(i=0;i<Acol;i++){
    P[i][i] = 1;
    L[i][i] = 1;
  }

  /*LU����*/
  LU_decomposition(A,L,U,P,Acol);

  /*�e�s��̕\��*/
  puts("�s��L");
  showMatrix((const double **)L,Arow,Acol);
  puts("�s��U");
  showMatrix((const double **)U,Arow,Acol);
  puts("�s��P");
  showMatrix((const double **)P,Arow,Acol);

  /*�����s��P�ƃx�N�g��b�̐ς��v�Z*/
  Pb = matrix_times_vector(P,b,Arow,Acol,brow);

  /*x,y�̃x�N�g����p��*/
  y = allocVector(bcol);
  x = allocVector(bcol);

  /*�O�i���*/
  foward(L,y,Pb,Arow);
  /*��ޑ��*/
  backward(U,x,y,Arow);

  /*����\��*/
  puts("�x�N�g��x");
  showVector((const double *) x,Arow);

	/*�������̉��*/
  freeMatrix(A);
  freeMatrix(L);
  freeMatrix(U);
  freeMatrix(P);
  freeMatrix(matrix);
  freeVector(b);
  freeVector(Pb);
  freeVector(x);
  freeVector(y);

	/*�t�@�C�������*/
	fclose(f1);
	fclose(f2);
}
