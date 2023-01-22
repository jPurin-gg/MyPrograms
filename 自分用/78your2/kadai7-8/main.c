//�����@�ɂ���čő�ŗL�l�ƍŏ��ŗL�l�����߂�v���O����

#include<math.h>
#include "NAbasic.h"

#define EPSILON 1.0e-8          //�ł��~�ߌ덷
#define ROW 10
#define LOOPLIMIT 150           //�������

//�v���g�^�C�v�錾
int findPivot(double **matrix, int top, int row);                                                               //�s�{�b�g��������
void swapLine(double **matrix1, int pivot, int top, int row, int col);                                          //����ւ���
void erase(double **matrix, int pivot, int row, int col);                                                       //�O�i����
double *calcProduct(double **matrix, double *vector, int row, int col);                                         //�s��~�x�N�g��
void setDiagonalMatrix(double **matrix, int row, int col);                                                      //�Ίp������1�ɂ���
double calcInnerProduct(double *vector1, double *vector2, int row);                                             //���ϋ��߂�
void forwardSubstitution(double **matrixL, double *y, double *Pb, int row);                                     //�O�i���
void backSubstitution(double **matrixU, double *x, double *y, int row);                                         //��ޑ��
int normalize(double *vector, int row);                                                                         //���K��

void generateLU(double **matrixL, double **matrixU, double **matrixA, double **matrixP, int row, int col);      //LU����
double calcMaxEigenvalue(double **matrixA, int row);                                                            //�ő�ŗL�l
double calcMinEigenvalue(double **matrixInverseA, double **matrixL, double **matrixU, int row);                 //�ŏ��ŗL�l

int main(int argc, char **argv) {
    FILE *fp;          
    double **a, **l, **u, **p;  //�s��       
    double maxLambda, minLambda;          
    int row, col;               //�s�A��

    //�t�@�C���I�[�v���Acsv�t�@�C���Ǎ�
    if (argc != 2) {
        fprintf(stderr, "�R�}���h���C���������s�����Ă��܂�\n");
        return EXIT_FAILURE;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
       	fprintf(stderr, "�t�@�C����: %s ���J���܂���ł���\n", argv[1]);
        return EXIT_FAILURE;
    }
    //�s��A�x�N�g�����̃������m�ہA�\��
    a = csvRead(&row, &col, fp);
    l = allocMatrix(row, col);
    u = allocMatrix(row, col);
    p = allocMatrix(row, col);
    printf("A�s��:\n");
    showMatrix((const double**)a, row, col);

    //L�s��AU�s��𐶐�����
    generateLU(l, u, a, p, row, col);
    printf("L�s��:\n");
    showMatrix((const double**)l, row, col);
    printf("U�s��:\n");
    showMatrix((const double **)u, row, col);

    //�ő�ŗL�l�A�ŏ��ŗL�l�����߂�
    maxLambda = calcMaxEigenvalue(a, row);
    minLambda = calcMinEigenvalue(a, l, u, row);
    printf("�ő�ŗL�l:%lf\n�ŏ��ŗL�l:%lf\n", maxLambda, minLambda);

    //�������J���E�t�@�C���N���[�Y
    freeMatrix(a);
    freeMatrix(l);
    freeMatrix(u);
    freeMatrix(p);
    fclose(fp);
    return EXIT_SUCCESS;
}

/*---------------------------------------------------
�s�{�b�g�̍s��������֐�
����:�s��A�n�_�̍s�A�s��
�߂�l:�s�{�b�g�����݂���s
---------------------------------------------------*/
int findPivot(double **matrix, int top, int row) {
    int max = top;

    for (int i = top; i < row; i++) {     //�n�_����I�_�܂Ő�Βl���r
        if(fabs(matrix[max][top]) < fabs(matrix[i][top])) {
            max = i;
        }
    }
    return max;
}
/*---------------------------------------------------
�s�����ւ���֐�
����:�s��A�s�{�b�g�A�擪�̍s�A�s���A��
�߂�l:�Ȃ�
---------------------------------------------------*/
void swapLine(double **matrix1, int pivot, int top, int row, int col) {  
    double **temp = allocMatrix(row, col);
   
    for (int i = 0; i < col; i++) { //�s�{�b�g�̍s��擪�Ɠ���ւ���
        temp[0][i] = matrix1[top][i];
        matrix1[top][i] = matrix1[pivot][i];
        matrix1[pivot][i] = temp[0][i];
    }
    freeMatrix(temp);
}
/*---------------------------------------------------
�O�i����������֐�
����:�W���s��A�s�{�b�g�A�s���A��
�߂�l:�Ȃ�
---------------------------------------------------*/
void erase(double **matrix, int pivot, int row, int col) {
    double element;  //��������v�f�����Ă����ϐ�

    for (int i = pivot + 1; i < row; i++) { //�s�{�b�g�̍s�����̍s�ɂ��ď������s��
        element = matrix[i][pivot];     //�v�f��ۑ�  
        for(int j = pivot; j < col; j++) {  //���ӂ̊e�����ɂ��Čv�Z
            matrix[i][j] = matrix[i][j] - ((element * matrix[pivot][j]) / matrix[pivot][pivot]);
        }
    }
}
/*---------------------------------------------------
�s��ƃx�N�g���̐ς����߂�
����:�s��A�x�N�g���A�s���A��
�߂�l:�v�Z����(�s��)
---------------------------------------------------*/
double *calcProduct(double **matrix, double *vector, int row, int col) {
    double *answer = allocVector(row);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            answer[i] += matrix[i][j] * vector[j];
        }
    }
    return answer;
}
/*---------------------------------------------------
n�sn��̑Ίp������1�̑Ίp�s��𐶐�����֐�
����:�s��A�s���A��
�߂�l:�Ȃ�
---------------------------------------------------*/
void setDiagonalMatrix(double **matrix, int row, int col) {
    int i;
        for(i = 0; i < row; i++) {
            matrix[i][i] = 1;           //�Ίp������1����   
        }
}
/*---------------------------------------------------
���ς����߂�֐�
����:�x�N�g��2�A�s��
�߂�l:���ς̒l
---------------------------------------------------*/
double calcInnerProduct(double *vector1, double *vector2, int row) {
    double innerProduct = 0;

    for (int i = 0; i < row; i++) {
        innerProduct +=  vector1[i] * vector2[i];
    }
    return innerProduct;
}
/*---------------------------------------------------
LU�s������߂�֐�
����:L�s��AU�s��AA�s��AP�s��A�s���A��
�߂�l:�Ȃ�
---------------------------------------------------*/
void generateLU(double **matrixL, double **matrixU, double **matrixA, double **matrixP, int row, int col) {
    int pivot;
    int i, j;
    double temp; 

    //P�s��
    setDiagonalMatrix(matrixP, row, col);

    //U�s��
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixU[i][j] = matrixA[i][j];
        }
    }
    for(int k = 0; k < row -1; k++){
        pivot = findPivot(matrixU, k, row);            
        swapLine(matrixU, pivot, k, row, col);              
        swapLine(matrixA, pivot, k, row, col);
        swapLine(matrixP, pivot, k, row, col);  
                      
        erase(matrixU, k, row, col);                        
    }

    //L�s��
    setDiagonalMatrix(matrixL, row, col);       //�Ίp������1�ɂ���
    for (i = 0; i < row; i++) {           
        temp = 0;
        for (j = 0; j < i; j++) {        
                matrixL[i][j] = (matrixA[i][j] - temp) / matrixU[j][j];     //���ӂ̌���(temp)���E�ӂɈڍ����ČW��U�Ŋ���
                temp += matrixL[i][j] * matrixU[j][j + 1];
        }
    }
}
/*---------------------------------------------------
�O�i��������� Lz=y
����:L�s��Az�x�N�g���Ay�x�N�g���A�s��
�߂�l:�Ȃ�
---------------------------------------------------*/
void forwardSubstitution(double **matrixL, double *z, double *y, int row) {
	for (int i = 0; i < row; i++) {
        z[i] = y[i] / matrixL[i][i];
		for (int j = 0; j < i; j++) {
			z[i] -= z[j] * matrixL[i][j] / matrixL[i][i];
		}
        
	}
}
/*---------------------------------------------------
��ޑ��������
����:U�s��Ax�x�N�g���Ay�x�N�g���A�s��
�߂�l:�Ȃ�
---------------------------------------------------*/
void backSubstitution(double **matrixU, double *x, double *y, int row) {
	for (int i = (row - 1); i >= 0; i--) {
        x[i] = y[i] / matrixU[i][i];
		for (int j = (row - 1); j > i; j--) {
			x[i] -= x[j] * matrixU[i][j] / matrixU[i][i];
		}
	}
}
/*---------------------------------------------------
�x�N�g����P�ʃx�N�g���ɐ��K������
����: �x�N�g���A����
�߂�l: ����������0, ���s������1
---------------------------------------------------*/
int normalize(double *vector, int row) {
	double norm = 0; // �x�N�g���̃m����
	int i;

	// �x�N�g���̃m�����v�Z
	for (i = 0; i < row; i++) {
		norm += vector[i] * vector[i];
	}

	norm = sqrtf(norm);

	if (norm == 0) {        //0�x�N�g������
		puts("���K���ł��܂���ł���\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i < row; i++) {
		vector[i] /= norm;           // �e�v�f���m�����Ŋ���
	}

	return EXIT_SUCCESS;
}
/*---------------------------------------------------
�ő�ŗL�l�����߂�֐�
����:A�s��A�s��
�߂�l:�ő�ŗL�l
---------------------------------------------------*/
double calcMaxEigenvalue(double **matrixA, int row) {
    double lambdaPrev, lambda = 0;
    double yPrev[ROW];
    double *y = allocVector(row);
    int count = 0;

    printf("�ő�ŗL�l:");
    for (int i = 0; i < row; i++) {
        y[i] = 100.0;       //�K���Ȓl����
    }

    do {
        memcpy(yPrev, y, sizeof(double) * row);     //1�O��y�ɃR�s�[
        y = calcProduct(matrixA, y, row, row);      
        lambdaPrev = lambda;
        lambda = calcInnerProduct(y, y, row) / calcInnerProduct(y, yPrev, row); //���ςɂ��ŗL�l�v�Z
        normalize(y, row);
        count++;
    }while((fabs(lambda - lambdaPrev) / fabs(lambda) > EPSILON) && (count < LOOPLIMIT));       //�����ꂩ�𖞂����Ȃ���Δ�����
    
    printf("�����񐔂�%d��\n", count);
    freeVector(y);
    return lambda;
}
/*---------------------------------------------------
�ŏ��ŗL�l�����߂�֐�
����:A�s��AL�s��AU�s��A�s��
�߂�l:�ŏ��ŗL�l
---------------------------------------------------*/
double calcMinEigenvalue(double **matrixA, double **matrixL, double **matrixU, int row) {
    double lambdaPrev, lambda = 0;
    double yPrev[ROW];
    double *y = allocVector(row);
    double *z = allocVector(row);
    int count = 0;

    printf("�ŏ��ŗL�l:");
    for (int i = 0; i < row; i++) {
        y[i] = 100.0;           //�K���Ȓl����
    }

    do{
        memcpy(yPrev, y, sizeof(double) * row);
        forwardSubstitution(matrixL, z, yPrev, row);
        backSubstitution(matrixU, y, z, row);
        lambdaPrev = lambda;
        lambda = calcInnerProduct(y, yPrev, row) / calcInnerProduct(y, y, row);
        normalize(y, row);
        count++;
    }while((fabs(lambda - lambdaPrev) / fabs(lambda) > EPSILON) && (count < LOOPLIMIT));

    printf("�����񐔂�%d��\n", count);
    freeVector(y);
    return lambda;
}



