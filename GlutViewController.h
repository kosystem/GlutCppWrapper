#ifndef GLUTVIEWCONTROLLER_H
#define GLUTVIEWCONTROLLER_H

#include "GlutCppWrapper.h"

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
    virtual void display();

    virtual void mouse(int button, int state, int x, int y);
    virtual void motion(int x, int y);
    virtual void mouseWheel(int wheel, int direction, int x, int y);

  protected:
    void incrimentCameraAngle(float dPan, float dTilt);
    void moveLookAtPoint(int dx, int dy);
    void drawAxis(float lenght);
    MouseState mouseState;
  };
}
#endif // GLUTVIEWCONTROLLER_H
