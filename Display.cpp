#include <GL/glut.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include "TextureManager.h"
#include "types.h"
#include "constants.h"
#include "Display.h"
#include "utils.h"

void Display::load() {
  this->bone_texture = TextureManager::Inst()->LoadTexture(
    "bone.jpg",
    GL_BGR_EXT,
    GL_RGB
  );
  int count = 0;
  int total = 0;
  for (int i = 0; i < NUM_FILES; ++i) {
    cv::Mat image = cv::imread(
      FILES[i],
      CV_LOAD_IMAGE_COLOR
    );
    if(! image.data ) {
      printf("Could not open or find the image %s\n", FILES[i].c_str());
      return;
    }

    SPARSE_MATRIX tmp, contour;
    for (int row = 0; row < image.rows; ++row) {
      uchar *ptr = image.ptr(row);
      for (int col = 0; col < image.cols; ++col) {
        if (ptr[0] && ptr[1] && ptr[2]) {
          ptr[0] = 255;
          ptr[1] = 255;
          ptr[2] = 255;
        }
        ptr += 3;
      }
    }

    cv::Mat canny_bone;
    cv::Canny(image, canny_bone, 0, 10);

    for (int row = 0; row < canny_bone.rows; ++row) {
      uchar *ptr = canny_bone.ptr(row);
      for (int col = 0; col < canny_bone.cols; ++col) {
        if (ptr[0]) {
          tmp[std::make_pair(row, col)] = 1;
          ++total;
        }
        ptr += 1;
      }
    }
    //count += hide_invisible(tmp, contour);
    this->images_vector.push_back(tmp);
  }
  count += get_reduced_cube(this->images_vector);
  printf("TOTAL: %d\n", total);
  printf("REDUCIDO: %d\n", count);
  printf("MOSTRADO: %d\n", total - count);
}

void Display::show() {
  glTranslatef(-40, START_Y, 0);
  int count_total = 0;
  for (int i = 0; i < this->images_vector.size(); ++i) {
    for (auto it = this->images_vector[i].begin();
         it != this->images_vector[i].end();
         ++it) {
      if (it->second > 0) {
        glPushMatrix();
          glColor3d(255, 255, 255);
          glTranslatef(
            float(it->first.first) * 0.29f,
            -float(i) * 0.5,
            float(-it->first.second) * 0.29f
          );
          //glutSolidCube(1);
          glBindTexture(GL_TEXTURE_2D, this->bone_texture);
          DrawParallelepiped(0.29, 0.5 * it->second, 0.29, GL_QUADS);
        glPopMatrix();
        ++count_total;
      }
    }
  }
}
