#include "NAbasic.h"

// IEEE754�`���ɕϊ����ďo��
void IEEE754_conversion(char *c) {
  int i, j, k;
  double ieee = 0.0;

  printf("sEEEEEEE EEEEdddd dddddddd... \n");

  // for (i = sizeof(double) - 1; i >= 0; i--) {
  //   for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--) {
  //     k = c[i] & (1 << j);
  //     printf("%d", k ? 1 : 0);
  //   }
  //   printf(" ");
  // }
  // printf("\n");

  // c�̒��g��sEEEEEEE EEEEdddd dddddddd...�@������
  for (i = 0; i < 8 * sizeof(double); i++) {
    if (c[i] == '1') {
      ieee += (1 << i);
      printf("1");
    } else {
      printf("0");
    }
  }

  printf("����:%.4lf\n", ieee);
}

int main(int argc, char **argv) {
  FILE *fin;
  double **matrix;
  int row, col;

  char c[sizeof(double) * 8];

  fgets(c, sizeof(double) * 8, stdin);
  for (int i = 0; i < 64; i++) printf("%c", c[i]);
  printf("\n");
  IEEE754_conversion(c);

  return 0;
}