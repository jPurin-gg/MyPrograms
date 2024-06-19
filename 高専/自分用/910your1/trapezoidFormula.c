//trapezoidFormula.c
#include <stdio.h>

double func(double x);

int main(){

double a0;//������
double a1,a2;//�ϕ��͈�
float fa0,fa1,fa2;
double s,sum = 0.0;
FILE *fp;

  //csv�t�@�C������x,y�̒l��ǂݍ���
  if ((fp = fopen("k10-input.csv", "r")) == NULL) return 0;
      while(fscanf(fp, "%f, %f, %f ", &fa0, &fa1, &fa2) != EOF) {
          a0 = (double)fa0;
          a1 = (double)fa1;
          a2 = (double)fa2;
      }
  fclose(fp);

double split = (a2 - a1) / a0;//���ݕ�

for(int i = 0; i < a0; i++){
  //��`�̖ʐς����߂�
  s = ((func(a1 + split*i) + func(a1 + split*(i+1))) / 2.0) * split;
  sum += s;
}

printf("�v�Z���� = %lf\n",sum);
return 0;
}

double func(double x){
  return x*x;
}
