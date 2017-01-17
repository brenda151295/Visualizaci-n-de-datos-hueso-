#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
  float translate_x;
  float translate_y;
  float translate_z;
  float delta_x;
  float delta_y;
  float mouse_x;
  float mouse_y;
 public:
  Camera() {
    this->translate_x = 0;
    this->translate_y = 0;
    this->translate_z = 0;
    this->delta_x = 0;
    this->delta_y = 0;
    this->mouse_x = 0;
    this->mouse_y = 0;
  }
  ~Camera() {}
  void update();
  void callback_mouse(int button, int state, int x, int y);
  void callback_motion(int x, int y);
  void key_up() {
    this->translate_z += 5.5f;
  }
  void key_down() {
    this->translate_z -= 5.5f;
  }
  void key_left() {
    this->translate_x -= 5.5f;
  }
  void key_right() {
    this->translate_x += 5.5f;
  }
};

#endif
