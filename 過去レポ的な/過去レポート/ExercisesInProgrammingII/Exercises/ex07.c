#include <math.h>
#include <GL/glut.h>

void display(void);
void dispXYZ(void);
void dispTetrahedron(void);
void resize(int w, int h);
void init(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	dispXYZ();
	dispTetrahedron();

	glFlush();
}

void dispXYZ(void)
{
	glBegin(GL_LINES);

	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);

	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);

	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);

	glEnd();
}

void dispTetrahedron(void)
{
	int i, j;

	GLdouble p[4][3];

	p[0][0] = 1.0;
	p[0][1] = p[0][2] = p[1][2] = 0.0;
	p[1][0] = p[2][0] = p[3][0] = -1.0 / 3;
	p[2][1] = p[3][1] = -sqrt(2.0) / 3;
	p[1][1] = -2.0 * p[2][1];
	p[2][2] = sqrt(6.0) / 3;
	p[3][2] = -p[2][2];

	glBegin(GL_LINES);

	for (i = 0; i < 3; i++)
	{
		for (j = i + 1; j < 4; j++)
		{
			glVertex3dv(p[i]);
			glVertex3dv(p[j]);
		}
	}

	glEnd();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(0.5, 1, 1, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();

	return 0;
}
