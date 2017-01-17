#include <iostream>
#include <GL/glut.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "constants.h"
#include "Split.h"

void Split::update() {
  if (this->is_active) {
    // printf("%f\n", (this->position_y) / -0.5f);
    glPushMatrix();
      glTranslatef(
        0,
        this->position_y,
        0
      );
      glTranslatef(0, 0, -50);
      glTranslatef(20, 0, 0);
      glColor4f(.23,.78,.32,0.1);
      glBegin(GL_QUADS);
        glVertex3d(-90, 0, -90);
        glVertex3d(-90, 0, 90);
        glVertex3d(90, 0, 90);
        glVertex3d(90, 0, -90);
      glEnd();
    glPopMatrix();
  }
  if (this->show_bone_image) {
    glPushMatrix();
      glTranslatef(0, -400, 0);

      glColor4f(.23,.78,.32,0.1);
      glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
        glVertex3d(325, -25, 5);

         glTexCoord2f(0.0, 1.0f);
        glVertex3d(325, 325, 5);

         glTexCoord2f(1.0, 1.0f);
        glVertex3d(-325, 325, 5);

         glTexCoord2f(1.0, 0.0);
        glVertex3d(-325, -25, 5);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture[0]);               
      glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
        glVertex3d(300, 0, 10);

         glTexCoord2f(0.0, 1.0f);
        glVertex3d(300, 300, 10);

         glTexCoord2f(1.0, 1.0f);
        glVertex3d(-300, 300, 10);

         glTexCoord2f(1.0, 0.0);
        glVertex3d(-300, 0, 10);
      glEnd();
    glPopMatrix();
    //printf("bone image\n");
  } else {
  }
}

void Split::show_images() {
  int pos = this->real_position();
  if (
      (pos >= 0) &&
      (pos < NUM_FILES)
     ) {
    this->get_images(pos);
  }
}

void Split::get_images(int id) {
  this->image = cv::imread(
    FILES[id],
    CV_LOAD_IMAGE_COLOR
  );
  if(! this->image.data ) {
    printf("Could not open or find the image %s\n", FILES[id].c_str());
    return;
  }

  for (int row = 0; row < this->image.rows; ++row) {
    uchar *ptr = this->image.ptr(row);
    for (int col = 0; col < this->image.cols; ++col) {
      if (ptr[0] && ptr[1] && ptr[2]) {
        ptr[0] = 255;
        ptr[1] = 255;
        ptr[2] = 255;
      }
      ptr += 3;
    }
  }

  cv::Canny(this->image, this->canny, 100, 50);

  for (int row = 0; row < this->canny.rows; ++row) {
    uchar *ptr = this->canny.ptr(row);
    for (int col = 0; col < this->canny.cols; ++col) {
      if (ptr[0] && ptr[1] && ptr[2]) {
        ptr[0] = 255;
        ptr[1] = 255;
        ptr[2] = 255;
      }
      ptr += 3;
    }
  }

  glGenTextures(1, &this->texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);               
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexImage2D(
    GL_TEXTURE_2D, 0, 3, this->image.cols, this->image.rows, 0, GL_RGB,
    GL_UNSIGNED_BYTE, this->image.data);

  //printf("\ntexture loaded %d \n", this->texture[0]);
  this->show_bone_image = ! this->show_bone_image;



}
