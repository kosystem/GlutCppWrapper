#ifndef GLUTVIEWCONTROLLER_H
#define GLUTVIEWCONTROLLER_H

#include "GlutCppWrapper.h"
#include "ModelLoader.h"

namespace glutCppWrapper{

typedef struct MouseStruct{
  int button;
  bool pressed;
  int x;
  int y;
}MouseState;

class GlutViewController : public GlutCppWrapper
{
public:
  GlutViewController();
  virtual void display(double dt);
  virtual void load();

  virtual void mouse(int button, int state, int x, int y);
  virtual void motion(int x, int y);
  virtual void mouseWheel(int wheel, int direction, int x, int y);

protected:
  void incrimentCameraAngle(float dPan, float dTilt);
  void moveLookAtPoint(int dx, int dy);
  void drawAxis(float lenght);
  void overlayDispray(char *string, int x, int y);
  void drawModel(ModelLoader model);
  MouseState mouseState;
  ModelLoader cubeModel;
};

} //namespace glutCppWrapper
#endif // GLUTVIEWCONTROLLER_H
