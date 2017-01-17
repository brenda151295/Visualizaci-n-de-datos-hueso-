#define GLUT_DISABLE_ATEXIT_HACK    

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "constants.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "App.h"

App app;

void glPaint(void) {
  app.glPaint();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
  app.window_reshape(width, height);
}

GLvoid window_key(unsigned char key, int x, int y) {
  app.window_key(key, x, y);
}

GLvoid window_idle() {
  app.window_idle();
}

GLvoid callback_special(int key, int x, int y) {
  app.callback_special(key, x, y);
}

GLvoid callback_mouse(int button, int state, int x, int y) {
  app.callback_mouse(button, state, x, y);
}

GLvoid callback_motion(int x, int y) {
  app.callback_motion(x, y);
}

void runApp(int argc, char** argv) {
  glutInit(&argc, argv);
  app.init();
  glutDisplayFunc(glPaint);
  glutReshapeFunc(&window_reshape);
  glutKeyboardFunc(&window_key);
  glutSpecialFunc(&callback_special);
  glutMouseFunc(&callback_mouse);
  glutMotionFunc(&callback_motion);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glutIdleFunc(&window_idle);
  glutMainLoop();
}

int main(int argc, char** argv) {
  runApp(argc, argv);
  return 0;
}
