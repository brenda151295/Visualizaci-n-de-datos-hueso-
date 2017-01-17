#include <iostream>
#include <GL/glut.h>
#include "constants.h"
#include "App.h"

void App::init_GL(void) {

// BEGIN LIGHTING

  // Set lighting intensity and color
  GLfloat qaAmbientLight[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat qaDiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
  GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
  GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};
  // Light source position
  GLfloat qaLightPosition[]    = {0.5, 0, -3.5, 0.5};

  // Enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Set lighting intensity and color
  glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

  // Set the light position
  glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


  glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
  glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
  glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva

// END LIGHTING

  glEnable(GL_DEPTH_TEST);
  glClearColor(RED, GREEN, BLUE, ALPHA);
  glEnable(GL_TEXTURE_2D);

}

void App::window_reshape(GLsizei width, GLsizei height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 4.0/3.0f, 1, 4000);

  glMatrixMode(GL_MODELVIEW);
}

void App::window_key(unsigned char key, int x, int y) {
  switch (key) {
    case ECHAP:
      exit(1);
      break;
    default:
      break;
  }
}

void App::callback_special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      this->camera.key_up();
      glutPostRedisplay();
      break;

    case GLUT_KEY_DOWN:
      this->camera.key_down();
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:					
      this->camera.key_left();
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:				
      this->camera.key_right();
      glutPostRedisplay();
      break;

    case GLUT_KEY_PAGE_UP:
      this->split.key_page_up();
      glutPostRedisplay();
      break;

    case GLUT_KEY_PAGE_DOWN:
      this->split.key_page_down();
      glutPostRedisplay();
      break;

    case GLUT_KEY_HOME:
      this->split.turn_on_off();
      glutPostRedisplay();
      break;

    case GLUT_KEY_END:
      this->split.show_images();
      glutPostRedisplay();
      break;
  }
}
void App::callback_mouse(int button, int state, int x, int y) {
  this->camera.callback_mouse(button, state, x, y);
}

void App::callback_motion(int x, int y) {
  this->camera.callback_motion(x, y);
  glutPostRedisplay();						
}

void App::window_idle() {
  glutPostRedisplay();
}

void App::glPaint() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(RED, GREEN, BLUE, ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 1000);
  gluPerspective(45, 4.0/3.0f, 1, 4000);

  this->camera.update();
  this->display.show();
  this->split.update();

  glutSwapBuffers();
  glFlush();
}

void App::init() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);                  // Tamaño de la ventana
  glutInitWindowPosition(100, 100);              // Posicion de la ventana
  glutCreateWindow("Bone Visualization");
  this->init_GL();
}
