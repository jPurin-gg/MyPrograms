/*�ő�ŗL�l�ƍŏ��ŗL�l���v�Z*/
#include <math.h>
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*��Βl�֐�*/
#define EPS 10e-9

/*�s��̗v�f�������V���ȍs���Ԃ��֐�*/
double** copyMatrix(double **matrix,int row,int col){
  int i,j;
  double **newMatrix;
  newMatrix = allocMatrix(row,col);

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      newMatrix[i][j] = matrix[i][j];
    }
  }

  return newMatrix;
}

/*�s�̓���ւ����s���֐�*/
void swap(double **matrix,int row,int i,int pivot){
  double *tmp_vec = matrix[pivot];

  if(!(((0<=i)&&(i<row))&&((0<=pivot)&&(pivot<row)))){
    fprintf(stderr, "�s�̌����Ɏ��s���܂���\n");
    exit(EXIT_FAILURE);
  }

  matrix[pivot] = matrix[i];
  matrix[i] = tmp_vec;
}

/*�s��ς��v�Z����֐�*/
double** dot(double **A,int Arow,int Acol, double **B, int Brow, int Bcol){
	int i,j,k;
	double **result;

	/*�v�Z�\���𔻒�*/
	if(Acol != Brow){
		printf("�v�Z�ł��܂���");
		exit(EXIT_FAILURE);
	}

	/*2�����z���p��*/
	result = allocMatrix(Arow,Bcol);

	/*�s����v�Z*/
	for(i=0;i<Arow;i++){
		for(j=0;j<Bcol;j++){
			result[i][j]=0;
			for(k=0;k<Acol;k++){
				result[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	return result;
}

/*�O�i���*/
double** foward(double **L, double **Pb,int size){
  int i,j;
  double **y;
  y = allocMatrix(size,1);

  for(i=0;i<size;i++){
    y[i][0] = Pb[i][0]/L[i][i];
    for(j=0;j<i;j++){
      y[i][0] -= y[j][0]*L[i][j]/L[i][i];
    }
  }

  return y;
}

/*��ޑ��*/
double** backward(double **U,double **y,int size){
  int i,j;
  double **x;
  x = allocMatrix(size,1);

  for(i=size-1;i>=0;i--){
    x[i][0] = y[i][0]/U[i][i];
    for(j=i+1;j<size;j++){
      x[i][0] -= x[j][0]*U[i][j]/U[i][i];
    }
  }
  return x;
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

/*matrix�̋t�s��ƃx�N�g��b�̐ς��v�Z����*/
double** dotInverseMatrix(double **matrix,int Arow,int Acol,double **b, int brow, int bcol){
  int i,j;
  double **A,**L,**U,**P,**z,**Pb,**result;

  if((Acol!=Arow)||(Acol!=brow)||(bcol!=1)){
    fprintf(stderr, "�t�s��ƃx�N�g���̐ς̌v�Z�Ɏ��s\n");
		exit(EXIT_FAILURE);
  }

  /*�s����R�s�[*/
  A = copyMatrix(matrix,Arow,Acol);

  /*L,U,P�̍s��ƌ��ʊi�[�p�̔z���p��*/
  L = allocMatrix(Arow,Acol);
  U = allocMatrix(Arow,Acol);
  P = allocMatrix(Arow,Acol);
  result = allocMatrix(bcol,1);

  /*L,U,P��P�ʍs��ŏ�����*/
  for(i=0;i<Arow;i++){
    for(j=0;j<Acol;j++){
      U[i][j] = L[i][j] = P[i][j] = (i==j) ? 1 : 0;
    }
  }

  /*LU����*/
  LU_decomposition(A,L,U,P,Acol);

  /*�����v�Z*/
  Pb  = dot(P,Arow,Acol,b,brow,bcol);
  z = foward(L,Pb,Arow);
  result = backward(U,z,Arow);

  /*���������i�[*/
  freeMatrix(A);
  freeMatrix(L);
  freeMatrix(U);
  freeMatrix(P);
  freeMatrix(z);
  freeMatrix(Pb);

  return result;
}

/*L2�m�������v�Z����֐�*/
double L2_norm(double **vec,int row,int col){
	int i;
	double norm = 0;

	/*��x�N�g�����m�F*/
	if(col!=1){
		fprintf(stderr, "L2�m�����̌v�Z�Ɏ��s\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<row;i++)	norm += vec[i][0]*vec[i][0];
	return sqrt(norm);
}

/*�x�N�g���̑傫����1�ɐ��K������֐�*/
void normalizeVector(double **vector,int row,int col){
  int i;
  double norm;
  if(col!=1){
    fprintf(stderr,"�x�N�g���̃m�����v�Z�Ɏ��s\n");
    exit(EXIT_FAILURE);
  }

  norm = L2_norm(vector,row,col);
  for(i=0;i<row;i++) vector[i][0] /= norm;
}

/*���ς��v�Z����֐�*/
double inner_product(double **a,int arow,int acol,double **b,int brow,int bcol){
  double result;
  double **matrix,**aT;
  /*���ς��v�Z�\�����ׂ�*/
  if((acol!=1)||(bcol!=1)||(arow!=brow)){
    fprintf(stderr, "���ς��v�Z�ł��܂���\n");
    //exit(EXIT_FAILURE);
  }

  /*�s��a��]�u*/
  aT = tpMatrix((const double**)a,arow,acol);

  /*�s��̐ς��v�Z*/
  matrix = dot(aT,acol,arow,b,brow,bcol);

  result = matrix[0][0];
  freeMatrix(aT);
  freeMatrix(matrix);

  return result;
}

/*�ő�ŗL�l���v�Z����֐�*/
double calcMaxEigen(double **matrix,int row,int col){
  int i;
  double lambda1=0,lambda2=0;
  double **y[2];
  /*��x�N�g����2�p�ӂ���*/
  y[0] = allocMatrix(row,1);
  y[1] = allocMatrix(row,1);
  /*��x�N�g���̏�����*/
  for(i=0;i<row;i++) y[0][i][0] = 1.0;

  i = 0;
  while((i<2)||(ABS((lambda2 - lambda1)/lambda1) > EPS)){
    lambda1 = lambda2;
    normalizeVector(y[i%2],row,1);  /*�x�N�g���̐��K��*/
    y[(i+1)%2] = dot(matrix,row,col,y[i%2],row,1);  /*�s�����x�|����*/

    /*�����_���v�Z*/
    lambda2 = inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1)
      /inner_product(y[(i+1)%2],row,1,y[i%2],row,1);

    i++;
  }

  /*�������̊J��*/
  freeMatrix(y[0]);
  freeMatrix(y[1]);

  return lambda2;
}

/*�ŏ��ŗL�l���v�Z*/
double calcMinEigen(double **matrix,int row,int col){
  int i;
  double lambda1=0,lambda2=0;
  double **y[2];
  /*��x�N�g����2�p�ӂ���*/
  y[0] = allocMatrix(row,1);
  y[1] = allocMatrix(row,1);

  /*��x�N�g���̏�����*/
  for(i=0;i<row;i++) y[0][i][0] = 1.0;

  i = 0;
  while((i<2)||(ABS((lambda2 - lambda1)/lambda1) > EPS)){
    lambda1 = lambda2;
    normalizeVector(y[i%2],row,1);  /*�x�N�g���̐��K��*/
    y[(i+1)%2] = dotInverseMatrix(matrix,row,col,y[i%2],row,1); /*�t�s�����x�|����*/

    /*�����_���v�Z*/
    double a,b;
    a = inner_product(y[(i+1)%2],row,1,y[i%2],row,1);
    b = inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1);
    printf("%f/%f\n",a,b);
    lambda2 = a/b;
    /*
    lambda2 = inner_product(y[(i+1)%2],row,1,y[i%2],row,1)
      /inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1);
    */
    i++;
  }
  /*�������̊J��*/
  freeMatrix(y[0]);
  freeMatrix(y[1]);

  return lambda2;
}


int main(int argc, char ** argv){
	FILE *f;
	int row,col;
  double max_lambda,min_lambda;
	double **matrix;

	/*�R�}���h���C�������̊m�F*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s matrix_CSV \n", argv[0]);
		return EXIT_FAILURE;
	}

	/*�s���CSV�t�@�C���̓ǂݍ���*/
	if((f  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}

  /*���͂��i�[*/
	matrix = csvRead(&row,&col,f);

  /*�����s�񂩂ǂ����m�F*/
  if(col != row){
    fprintf(stderr, "���͂������s��ł͂���܂���.\n");
		return EXIT_FAILURE;
  }

  /*�ő�&�ŏ��ŗL�l���v�Z*/
  max_lambda = calcMaxEigen(matrix,row,col);
  min_lambda = calcMinEigen(matrix,row,col);

  /*�o��*/
  printf("�ő�ŗL�l:%f\n",max_lambda);
  printf("�ŏ��ŗL�l:%f\n",min_lambda);

  /*�������̊J��*/
  freeMatrix(matrix);
  free(f);

  return 0;
}
