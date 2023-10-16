#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>

GLdouble vP[4][3]={
	{1.000,0.000,0.000},
	{-0.333,0.943,0.000},
	{-0.333,-0.471,0.816},
	{-0.333,-0.471,-0.816}
};

int tP[4][3]={
	{0,1,2},{0,3,1},
	{0,2,3},{1,3,2}
};


GLdouble cP[4][3]={
	{1.0,0.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,1.0,0.0}
};

GLdouble cP2[4][3]={
	{1.0,0.0,1.0},{0.5,1.0,0.0},
	{0.5,0.0,1.0},{0.7,0.0,333.333}
};

int rotate = 0;

void display(){

	int i,j;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_TRIANGLES);
	for(i=0;i<4;i++){
		glColor3dv(cP[i]);
		for(j=0;j<3;j++){
			glVertex3d((vP[tP[i][j]][0]+1),(vP[tP[i][j]][1]),(vP[tP[i][j]][2]));
		}
	}
	
		for(i=0;i<4;i++){
		glColor3dv(cP2[i]);
		for(j=0;j<3;j++){
			glVertex3d((vP[tP[i][j]][0]-1),(vP[tP[i][j]][1]),(vP[tP[i][j]][2]));
		}
	}
	
	glEnd();
	glutSwapBuffers();

}

void init(){

	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(0,0,5,0,0,0,0,1,0);
	glEnable(GL_CULL_FACE);

}

void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7,7,-7,7,-7,7);

}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glMatrixMode(GL_MODELVIEW);
	switch(rotate){
		case 1:glRotated(3.0,1.0,0.0,0.0);break;
		case 2:glRotated(3.0,0.0,1.0,0.0);break;
		case 3:glRotated(3.0,0.0,0.0,1.0);break;
		default:break;
	}
	glutPostRedisplay();

}

void keyin(
	unsigned char key,int x, int y
){
	switch(key){
		case 'p': rotate = 0;break;
		case 'x': rotate = 1;break;
		case 'y': rotate = 2;break;
		case 'z': rotate = 3;break;
		case 'q': exit(0);
		default: break;
	}
}

int main(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutTimerFunc(100,timer,0);
	glutKeyboardFunc(keyin);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;

}
