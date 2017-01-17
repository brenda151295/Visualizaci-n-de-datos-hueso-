#ifndef _APP_H
#define _APP_H

#include "Camera.h"
#include "Split.h"
#include "Display.h"

class App {
  Camera camera;
  Display display;
  Split split;
  int time_;
  int timebase;
 public:
  App() {
      time_ = 0;
      timebase = 0;
  }
  ~App() {}
  void static init_GL(void);
  void window_reshape(GLsizei width, GLsizei height);
  void window_key(unsigned char key, int x, int y);
  void callback_special(int key, int x, int y);
  void callback_mouse(int button, int state, int x, int y);
  void callback_motion(int x, int y);
  void window_idle();
  void glPaint();
  void init();
};

#endif
