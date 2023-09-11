#include <GL/glut.h>

void display() { /* 描画命令 */

  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void init() { /* 初期化命令 */

  glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();

  return 0;
}