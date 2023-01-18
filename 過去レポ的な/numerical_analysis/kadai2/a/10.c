/*x^2�̐ϕ������߂�*/
#include "NAbasic.h"
#define F(x) (x)*(x) /*�ϕ�����֐�*/

/*
��`�����ɂ���Đϕ����v�Z����֐�
����
  n:������
  a1,a2:�ϕ����
�o��
  result:�ϕ��l
*/
double trapezoidal(int n,int a1,int a2){
  int i;
  double result=0,h;
  /*���������v�Z*/
  h = (double)(a2-a1)/n;

  for(i=1;i<n;i++) result += F(a1+h*i);
  result*=2;

  /*�[�_�̒l���v�Z*/
  result+=F(a1)+F(a2);

  return result*h/2;
}

/*
Simpson�����ɂ���Đϕ����v�Z����֐�
����
  n:������
  a1,a2:�ϕ����
�o��
  result:�ϕ��l
*/
double integral(int n,int a1,int a2){
  int i;
  double result=0,h,sum=0;

  if(n%2!=0){
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
  }
  /*���������v�Z*/
  h = (double)(a2-a1)/n;

  /*�[�_�̒l���v�Z*/
  result += F(a1) + F(a2);

  /*��Ԗڂ̓_�̒l�̘a���Ƃ�*/
  for(i=1;i<=n-1;i+=2) sum += F(a1+h*i);

  result += 4*sum;

  /*�����Ԗڂ̓_�̒l�̘a���Ƃ�*/
  sum = 0;
  for(i=2;i<=n-2;i+=2) sum += F(a1+h*i);

  result += 2*sum;

  return h*result/3;
}

/*
�����o�[�O�@�ɂ���Đϕ����v�Z����֐�
����
  n:������
  a1,a2:�ϕ����
�o��
  result:�ϕ��l
*/
double Romberg(int N,double a1,double a2){
  int i,k,m,n,p;
  double h,sum;
  double T[20][20];

  T[0][0]=(a2-a1)*(F(a2)+F(a1))/2;

  n=1;

  for(k=1;k<N;k++){
    /*�������𑝂₷*/
    n*=2;
    h=(a2-a1)/n;
    sum=0;
    for(i=1;i<=n;i++)
      if(i%2==1) sum+=F(a1+i*h);

    T[k][0] = T[k-1][0]/2 + h*sum;

    /*�����𑝂₷*/
    p=1;
    for(m=1;m<=k;m++){
      p*=2;
      T[k][m] = T[k][m-1] + (T[k][m-1] - T[k-1][m-1])/(p*p-1);
    }
  }

  /*���ʂ�\��*/
  printf("������:%d�@����:%d\n",n,p);
  puts("Romberg Table");
  for(k=0;k<N;k++){
    for(m=0;m<=k;m++){
      printf("%.10f  ",T[k][m]);
    }
    putchar('\n');
  }

  printf("�ϕ��l%f\n",T[N-1][N-1]);

  return 0;
}

int main(int argc, char ** argv){
	FILE *f;
	int row,col;
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
	if((col != 3)||(row !=1 )){
		fprintf(stderr, "���͂��Ⴂ�܂�\n");
		return 0;
	}
  printf("��`����==>%f\n",trapezoidal(matrix[0][0],matrix[0][1],matrix[0][2]));
  printf("Simpson����==>%f\n",integral(matrix[0][0],matrix[0][1],matrix[0][2]));
}
