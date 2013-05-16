#ifndef GLUTCPPWRAPPER_H
#define GLUTCPPWRAPPER_H
#include "GL/freeglut.h"

#include <float.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

namespace glutCppWrapper {
typedef struct CameraStruct{
  float lock_x;
  float lock_y;
  float lock_z;
  float pan;
  float tilt;
  float distance;
}Camera;

class GlutCppWrapper
{
public:
  const static int WINDOW_WIDTH = 640;
  const static int WINDOW_HEIGHT = 480;
  const static int WINDOW_X_POSITION = 100;
  const static int WINDOW_Y_POSITION = 100;

protected:
  std::string title;

public:
  GlutCppWrapper();

  virtual void load();
  virtual void display();
  virtual void reshape(int width, int height);
  virtual void idle();

  virtual void mouse(int button, int state, int x, int y);
  virtual void motion(int x, int y);
  virtual void passiveMotion(int x, int y);
  virtual void mouseWheel(int wheel, int direction, int x, int y);

  virtual void keyboard(unsigned char key, int x, int y);
  virtual void keyboardUp(unsigned char key, int x, int y);
  virtual void special(int key, int x, int y);
  virtual void specialUp(int key, int x, int y);

  void startFramework(int argc, char *argv[]);

  void setInstance();
  void displayFramework();

  void setCamera();
  void setupLights();


  static void displayWrapper();
  static void reshapeWrapper(int width, int height);
  static void idleWrapper();

  static void mouseWrapper(int button, int state, int x, int y);
  static void motionWrapper(int x, int y);
  static void passiveMotionWrapper(int x, int y);
  static void mouseWheelWrapper(int wheel, int direction, int x, int y);

  static void keyboardWrapper(unsigned char key, int x, int y);
  static void keyboardUpWrapper(unsigned char key, int x, int y);
  static void specialWrapper(int key, int x, int y);
  static void specialUpWrapper(int key, int x, int y);

protected:
  static GlutCppWrapper *instance;

  Camera camera;

};
}

#endif // GLUTCPPWRAPPER_H
