#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "types.h"

class Display {
  SPARSE_CUBE images_vector;
  GLuint bone_texture;
 public:
  Display() {
    this->load();
  }
  ~Display() {}
  void load();
  void show();
};

#endif
