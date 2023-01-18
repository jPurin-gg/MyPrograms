#include "NAbasic.h"
#include <math.h>

int main(int argc,char **argv){
	FILE *fp;
	int row,col;
	int i,j;
	double **temp, **xy;
	double P,input,seki=1;

	if((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr,"File: %s cannot open\n",argv[1]);
	}

	puts("x�̒l�����\n");
	scanf("%lf",&input);

	xy = csvRead(&row, &col, fp);//�v���f�[�^��ǂݍ���ł����s��
	temp = allocMatrix(row,row);
//3�_�𗘗p������Ԃɂ��y�̒l
	for(i = 0; i < row-1; i++){//���������v�Z���s��temp�ɑ��
		for(j = 0; j < (row-i-1); j++){
			if(i == 0) temp[j][i] = xy[j][1];//1��ڂɂ͑Ή�����y�̒l�����̂܂ܓ���
			else temp[j][i] = (temp[j+1][i-1] - temp[j][i-1]) / (xy[j+i][0] - xy[j][0]);//2��ڈȍ~�͍��������v�Z
		}
	}

	P = temp[0][0];

	for(i = 1; i < (row - 1); i++){//���Ɋ�Â����͂��ꂽx�̒l�ɑΉ�����y�̒l���v�Z
		for(j = 0; j < i; j++){
			seki = seki * (input - xy[j][0]);
		}
		P += seki * temp[0][i];
		seki = 1;
	}
	puts("3�_�𗘗p������Ԃɂ��y�̒l��\n");
	printf("%f\n",P);
//4�_�𗘗p������Ԃɂ��y�̒l
	for(i = 0; i < row; i++){
		for(j = 0; j < (row - i); j++){//�������Ƃ��낾���v�Z
			if(i == 0){
				if(j == (row - 1))temp[j][i] = xy[j][1];
			}else{
				if(j == (row - i - 1))temp[j][i] = (temp[j+1][i-1] - temp[j][i-1]) / (xy[j+i][0] - xy[j][0]);
			}
		}
	}

	for(j = 0; j < (row - 1); j++){
		seki = seki * (input - xy[j][0]);
	}
	P += seki * (temp[0][row-1]);//3�_�ɂ���Ԃ�y�̒l�ɑ������������Z

	puts("4�_�𗘗p������Ԃɂ��y�̒l��\n");
	printf("%f\n",P);

	freeMatrix(temp);
	freeMatrix(xy);
	fclose(fp);
	return EXIT_SUCCESS;
}