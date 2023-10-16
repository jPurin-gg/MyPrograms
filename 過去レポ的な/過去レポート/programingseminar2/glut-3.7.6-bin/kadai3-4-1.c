#include <GL/glut.h>
#include <math.h>

GLdouble vP[4][3]={{1.000,0.000,0.000},{-0.333,0.943,0.000},{-0.333,-0.471,0.816},{-0.333,-0.471,-0.816}};
int tP[4][3]={{0,1,2},{0,3,1},{0,2,3},{1,3,2}};

void display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_TRIANGLES);
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			glNormal3dv(vP[tP[i][j]]);
			glVertex3dv(vP[tP[i][j]]);
		}
	}
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();

}

void init(void){
	glClearColor(1.0,1.0,1.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/400.0,w/400.0,-h/400.0,h/400.0,-3,3);
}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}




void keyin(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a': glRotated(1, 1, 0, 0);glutPostRedisplay();break;
		case 's': glRotated(1, -1, 0, 0);glutPostRedisplay();break;
		case 'd': glRotated(1, 0, 1, 0);glutPostRedisplay();break;
		case 'f': glRotated(1, 0, -1, 0);glutPostRedisplay();break;
		case 'h': glRotated(1, 0, 0, 1);glutPostRedisplay();break;
		case 'j': glRotated(1, 0, 0, -1);glutPostRedisplay();break;
		case '\033': exit(0);
		default: break;
	}
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(700,300);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100,timer,0);
	glutKeyboardFunc(keyin);
	init();
	glutMainLoop();
	return 0;
}

