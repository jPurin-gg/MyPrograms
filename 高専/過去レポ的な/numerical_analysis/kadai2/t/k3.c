#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NAbasic.h"

/* �֐�f(x)�̒�` */
double f(double x){
    return x*x*x*x - 3*x*x + 5*x -9;
}

/* �֐�f(x)��x�Ŕ��������A�֐�f'(x)�̒�` */
double df(double x){
    return 4*x*x*x - 6*x + 5;
}

int main(int argc, char **argv){
    int i = 0;
    int row, col;
    double ah, a, b, c, s;
    double **matrix;
    FILE *fin;

    /* �K�؂ȃR�}���h���C���������^�����Ă��Ȃ��Ƃ��Ɍx������B */
    if(argc != 2){
        fprintf(stderr, "Usage: %s difficult\n", argv[0]);
        return EXIT_FAILURE;
    }
    if((fin = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "File: %s cannot open\n", argv[1]);
        return EXIT_FAILURE;
    }

    matrix = csvRead(&row, &col, fin); /* �f�[�^�ǂݍ��� */

    /* �͈͂�a����b�܂� */
    a = matrix[0][0];  
    b = matrix[0][1];
    /* �j���[�g���@�̏����l */
    c = (a + b)/2.0;

    /* 2���@�ŉ������߂�B10��ڂ܂ŌJ��Ԃ��Ȃ������\������B */
    while(i<10){
        i++;
        s = (a+b)/2.0;
        if((f(s) * f(a))<0) b=s;
        else a = s;
        printf("2���@�̉� : %f(�J��Ԃ���%d ��)\n", s, i);
    }

    i = 0;  /* i�̒l�����Z�b�g */
 
    /* �j���[�g���@�ŉ������߂�B10��ڂ܂ŌJ��Ԃ��Ȃ������\������B */
    while(i<10){
        i++;
        ah = c - f(c)/df(c);
        c = ah;
        printf("�j���[�g���@�̉� : %f(�J��Ԃ���%d ��)\n", c, i);
    }

    freeMatrix(matrix); /* ������ƌ㏈��������B */

    return EXIT_SUCCESS;
}