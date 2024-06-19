/*�A���ꎟ�������̔�����@*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*��Βl�֐�*/
#define N1 80 /*Jacobi�@�̌J��Ԃ���*/
#define N 10 /*Gauss-Seidel�@�̌J��Ԃ���*/

/*�x�N�g���̗v�f��\������֐�*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%.6f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

/*Jacobi�@*/
double* J_method(double **A,double *b,int size){
  int i,j,k;
  double L,R;
  double **x;
  x = allocMatrix(2,size);
  /*�v�f��0�ŏ�����*/
  for(i=0;i<size;i++) x[0][i] = x[1][i] = 0;

  /*����*/
  for(i=0;i<N1;i++){
    for(j=0;j<size;j++){
      L = R = 0;

      /*�Ίp�����̍���*/
      for(k=0;k<j;k++){
        L += A[j][k]*x[i%2][k];
      }

      /*�Ίp�����̉E��*/
      for(k=j+1;k<size;k++){
        R += A[j][k]*x[i%2][k];
      }

      x[(i+1)%2][j] = (b[j] - L - R)/A[j][j];
    }
  }

  return x[i%2];
}

/*Gauss-Seidel�@*/
double* GS_method(double **A,double *b,int size){
  int i,j,k;
  double L,R;
  double *x, *xn;
  x = allocVector(size);
  xn = allocVector(size);
  /*�v�f��0�ŏ�����*/
  
  for(i = 0; i < N; i++)
  {
    xn[i] = b[i];
    for(j = 0; j < i-1; j++)
    {
	xn[i] -= A[i][j]*xn[j];
    }
    for(j = i+1; j < N; j++)
    {
        xn[i] -= A[i][j]*x[j];
    }
    xn[i] /= A[i][i];
	x[i] = xn[i];
	printf("%f", x[i]);
  }
  return x;
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int Arow,Acol,brow,bcol;
	double **A,**matrix;
	double *x,*b;

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
		b = matrix2colVector((const double **)matrix,brow,bcol);
	}

	/*�A���ꎟ�������ƂȂ邩�m�F*/
	if((Acol != brow) && (Acol != Arow)){
		fprintf(stderr, "�A���ꎟ�������ƂȂ�܂���.\n");
		return EXIT_FAILURE;
	}

  /*Jacobi�@�ŉ������߂�*/
  x = J_method(A,b,Arow);

  /*���ʂ�\��*/
//  printf("Jacobi�@(����%d��)\n",N1);
//  showVector((const double *) x,Arow);

  /*Gauss-Seidel�@�ŉ������߂�*/
  x = GS_method(A,b,Arow);

  /*����\��*/
  printf("Gauss-Seidel�@(����%d��)\n",N);
  showVector((const double *) x,Arow);

	/*�������̉��*/
  freeMatrix(A);
  freeMatrix(matrix);
  freeVector(b);
  freeVector(x);

	/*�t�@�C�������*/
	fclose(f1);
	fclose(f2);
}
