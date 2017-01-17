#include <iostream>
#include <GL/glut.h>
#include "constants.h"
#include "Camera.h"

void Camera::update() {
  glTranslatef(0, 0, -750);
  glTranslatef(
    this->translate_x,
    this->translate_y,
    this->translate_z
  );
  glRotatef(this->delta_x, 0.0, 1.0, 0.0);
  glRotatef(this->delta_y, 1.0, 0.0, 0.0);

  if (BONE_COLOR) {
    glColor3d(BONE_COLOR_R, BONE_COLOR_G, BONE_COLOR_B);
  }

  // glColor3d(255, 0, 0);
  // glBegin(GL_LINES);
  // glColor3f(1.0f, 0.0f, 0.0f);
  // glVertex3f(0.0f, 0.0f, 0.0f);
  // glVertex3f(3.0f, 0.0f, 0.0f);
  // glEnd();

  // glColor3d(0, 255, 0);
  // glBegin(GL_LINES);
  // glColor3f(0.0f, 1.0f, 0.0f);
  // glVertex3f(0.0f, 0.0f, 0.0f);
  // glVertex3f(0.0f, 3.0f, 0.0f);
  // glEnd();

  // glColor3d(0, 0, 255);
  // glBegin(GL_LINES);
  // glColor3f(0.0f, 0.0f, 1.0f);
  // glVertex3f(0.0f, 0.0f, 0.0f);
  // glVertex3f(0.0f, 0.0f, 3.0f);
  // glEnd();
}

void Camera::callback_mouse(int button, int state, int x, int y) {
  if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    this->mouse_x = x;
    this->mouse_y = y;
  }
}

void Camera::callback_motion(int x, int y) {
  this->delta_x += x - this->mouse_x;
  this->delta_y += y - this->mouse_y;
  this->mouse_x = x;
  this->mouse_y = y;
  glutPostRedisplay();
}

