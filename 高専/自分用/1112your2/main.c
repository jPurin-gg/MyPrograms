// 12�T�ډۑ�
// �I�C���[�@�ɂ������������̉��̓��o

#include <stdio.h>

// �I�C���[�@�Ő��l�������߂�
int Euler(double x0, double h, double xm, double *y) {
  int a;
  double x;

  for (a = 1, x = 0; x < xm; a++) {
    x = x + h;
    y[a] = y[a - 1] + ((-(x - h) * y[a - 1] + (x - h)) * h);
    printf("x=%f,  ", x);
    printf("y=%lf\n", y[a]);
  }

  return 0;
}

int main(void) {
  FILE *fin;
  double y[1], h;
  double x0, xm, y0;
  /*
  x0 : x�̏����l
  h : �X�e�b�v��
  xm : x�̍ő�l
  y0 : y�̏����l
  */

  // csv�t�@�C������f�[�^��ǂݍ���
  fin = fopen("k12-input.csv", "r");
  if (!fin) {
    perror("fopen");
    return 1;
  }

  fscanf(fin, "%lf, %lf, %lf, %lf\n", &x0, &h, &xm, &y0);
  fclose(fin);

  printf("STEP : %lf\n", h);
  y[0] = y0;

  printf("Answer\n");
  printf("x=%lf,  y=%lf\n", x0, y[0]);
  Euler(x0, h, xm, y);  // �I�C���[�@�Ő��l�������߂�

  return 0;
}