#ifndef _SPLIT_H
#define _SPLIT_H

#include <opencv2/core/core.hpp>

class Split {
  GLuint texture[2];
  float position_y;
  bool is_active;
  bool show_bone_image;
  cv::Mat image;
  cv::Mat canny;
 public:
  Split() {
    this->position_y = 0;
    this->is_active = false;
    this->show_bone_image = false;
  }
  ~Split() {}
  void update();
  void key_page_up() {
    this->position_y += 0.2f;
    //get_images(position_y);
  }
  void key_page_down() {
    this->position_y -= 0.2f;
    //get_images(position_y);
  }
  void turn_on_off() {
    this->is_active = ! this->is_active;
  }
  int real_position() {
    return (int) (this->position_y / -0.5f);
    // return (int) ((this->position_y - START_Y) / -0.5f);
  }
  void show_images();
  void get_images(int);
};

#endif
