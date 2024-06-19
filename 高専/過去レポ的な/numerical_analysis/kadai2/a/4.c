/*�����s�|�b�g�I��t�K�E�X�̏����@*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*��Βl�֐�*/

/*�x�N�g���̗v�f��\������֐�*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%.4f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int row1,col1,row2,col2,i,j,k,pipot,pipot_val;
	double **matrix1,**matrix2;
	double *ans,*tmp_vec,*vector;
  double a,tmp;

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
	matrix1 = csvRead(&row1,&col1,f1);

	/*�x�N�g����CSV�t�@�C���̓ǂݍ���*/
	if((f2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "�t�@�C�������݂��܂���.\n");
		return EXIT_FAILURE;
	}
	matrix2 = csvRead(&row2,&col2,f2);

	/*�񎟌��z��ɒ���*/
	if(col2 != 1){
		fprintf(stderr, "�x�N�g�������͂���Ă��܂���.\n");
		return EXIT_FAILURE;
	}else{
		vector = matrix2colVector((const double **)matrix2,row2,col2);
	}

	/*�A���ꎟ�������ƂȂ邩�m�F*/
	if((col1 != row2) && (col1 != row1)){
		fprintf(stderr, "�A���ꎟ�������ƂȂ�܂���.\n");
		return EXIT_FAILURE;
	}

	/*�K�E�X�̏����@*/
	for(i=0;i + 1 < row1;i++){
		/*�s�|�b�g��I��*/
		pipot_val = -1;
		pipot = 0;

		for(j=i;j<row1;j++){
			if(ABS(matrix1[j][i]) > pipot_val){
				pipot_val = ABS(matrix1[j][i]);
				pipot = j;
			}
		}

		/*�s�̓���ւ�*/
		if(pipot != 0){
			tmp_vec = matrix1[pipot];
			matrix1[pipot] = matrix1[i];
			matrix1[i] = tmp_vec;

			tmp = vector[pipot];
			vector[pipot] = vector[i];
			vector[i] = tmp;
		}

		/*�O�i����*/
		for(j=i+1;j<row1;j++){/*�s*/
      a = matrix1[j][i]/matrix1[i][i];
			for(k=i;k<col1;k++){/*��*/
        matrix1[j][k] -= a*matrix1[i][k];
			}
			vector[j] -= a*vector[i];
		}
	}

  /*�����i�[�p�z���p��*/
  ans = allocVector(row1);

  /*�����*/
  for(i=row1-1;i>=0;i--){
      for(j=row1-1;j>i;j--){
          vector[i] -= matrix1[i][j]*ans[j];
      }
      ans[i] = vector[i]/matrix1[i][i];
  }

  /*���ʂ�\��*/
  showVector((const double *) ans,row1);

	/*�������̉��*/
  freeMatrix(matrix1);
  freeMatrix(matrix1);
	freeVector(vector);
  freeVector(tmp_vec);
  freeVector(ans);

	/*�t�@�C�������*/
	fclose(f1);
	fclose(f2);
}
