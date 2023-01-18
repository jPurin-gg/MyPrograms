#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define fmax 100                 //�J��Ԃ��ő��
#define eps 1.0e-5              //�ŏ��덷���e�͈�

int main(int argc, char **argv)
{ 
 FILE *fin; 
 double **matrix1, **matrix2;	/*�z��matrix1,matrix2�ɂ͌W���̒l�����B*/
 int row, col; 
 
 char c[sizeof(double)]; 
 int i, j, k, n;
 double err;
 
 /* CSV����Ώۃf�[�^��ǂݍ��� */ 
if (argc != 3) {
	fprintf(stderr, "Usage: %s decimal data \n", argv[0]); /* �s�K�؂ȓ��͂����ꂽ�Ƃ��Ɍx������ */
	return EXIT_FAILURE;
}
if ((fin = fopen(argv[1], "r")) == NULL) { /* read���[�h�Ńe�L�X�g�t�@�C�����J�� */
	fprintf(stderr, "File: %s cannot open\n", argv[1]);
	return EXIT_FAILURE;
}
matrix1 = csvRead(&row, &col, fin); /* csv�t�@�C��1��ǂݍ���matrix2�Ɋi�[����B NAbasic�Ŋ֐���` */

if ((fin = fopen(argv[2], "r")) == NULL) { /* read���[�h�Ńe�L�X�g�t�@�C�����J�� */
	fprintf(stderr, "File: %s cannot open\n", argv[2]);
	return EXIT_FAILURE;
}
matrix2 = csvRead(&row, &col, fin); /* csv�t�@�C��2��ǂݍ���matrix2�Ɋi�[����B NAbasic�Ŋ֐���` */

/*���R�r�@*/

/*�z��xold�ɂ͓K���Ɍ��߂����̒l�����Ă���*/
double xold[row],xnew[row];

for(n =0; n<row; n++){
	xold[n] = 1.0;
}

for(k=0;k<fmax;k++) {
	err=0.0;	//�덷�̃��Z�b�g
	for(i=0;i<row;i++) {
		xnew[i]=matrix2[i][0];
		for(j=0;j<n;j++) {
			if(j!=i) {
				xnew[i]-=matrix1[i][j]*xold[j];
			}
		}
		xnew[i]=xnew[i]/matrix1[i][i];
	}
/*�e���̌덷�𑫂��A�Â����͎̂Ĕz��xold�ɐV������������*/
	for(i=0;i<n;i++) {
		err+=fabs(xold[i]-xnew[i]);
		xold[i]=xnew[i];
	}
/*�������킳�ꂽ�덷�����e�͈͓���������
�v�Z�I���Ƃ��������܂����Ƃ���*/
	if(err<eps) break;
}

/*���܂��������o�͂���*/
printf("���R�r�@�ɂ�����\n");
for(i=0;i<n;i++) {
	printf("%8.4f\n",xnew[i]);
}

/*�J��Ԃ��񐔂��ő�񐔂̒l��������
���m�ȉ������܂��Ă��Ȃ��\����Ȃ̂Œ���*/
printf("�J��Ԃ��񐔂� %d\n",k+1);

/*�K�E�X�U�C�f���@*/

double xn = 0.0, dx, absx, sum;

k = 1;
for(n =0; n<row; n++){
	xnew[n] = 1.0;
}

do{	// �����v�Z�̃��[�v
	dx = 0.0;
	absx = 0.0;
	k++;
	for(i=0; i<row; i++){
		sum = 0;
		for(j=0; j<row; j++){
			if(i != j){
				sum+=matrix1[i][j]*xnew[j];
			}
		}
		xn = 1.0/matrix1[i][i]*(*matrix2[i] - sum);	// �����v�Z��̋ߎ���
		dx += fabs(xn-xnew[i]);	// �ߎ����̕ω��ʂ����Z
		absx += fabs(xn);	// �ߎ����̑��a�v�Z
		xnew[i] = xn;	// �V�����ߎ�������
	}
}while(dx/absx > eps);	// �v�Z�I������

/*���܂��������o�͂���*/
printf("�K�E�X�E�U�C�f���@�ɂ�����\n");
for(i=0; i<row; i++){
	printf("%8.4f\n",xnew[i]);
}
printf("�J��Ԃ��񐔂� %d\n",k);

	return 0;
}
