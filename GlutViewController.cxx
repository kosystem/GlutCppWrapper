#include "GlutViewController.h"
#include <string.h>

namespace glutCppWrapper{
GlutViewController::GlutViewController()
{
  mouseState.button = 0;
  mouseState.pressed = false;
  mouseState.x = 0;
  mouseState.y = 0;
}

void GlutViewController::display()
{
  float opacity = 0.5;
  GLfloat green[] = { 0.2, 1.0, 0.2, opacity };
  GLfloat red[]   = { 1.0, 0.2, 0.2, opacity };
  GLfloat blue[]  = { 0.3, 0.3, 1.0, opacity };
  GLfloat black[] = { 0.0, 0.0, 0.0, opacity };
  GLfloat yellow[] = { 0.9, 0.9, 0.0, opacity };
  GLfloat lightGray[] = { 0.7, 0.7, 0.7, opacity };
  GLfloat pink[] = { 1.0, 0.0, 1.0, opacity };

  glPushMatrix();
  glTranslated(camera.lock_x, camera.lock_y, camera.lock_z);
  drawAxis(10);
  glPopMatrix();

  glPushMatrix();

//  glDisable(GL_DEPTH_TEST);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightGray);
  drawModel(cubeModel);

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
  glTranslated(10.0, 0.0, 0.0);
  drawModel(cubeModel);

//  glEnable(GL_DEPTH_TEST);
//  glDisable(GL_BLEND);

  glPopMatrix();

  char string[] = "Test message";
  overlayDispray(string, 0, 0);
}

void GlutViewController::load()
{
  cubeModel.loadSTL("./cube-binary.stl");
}


void GlutViewController::drawAxis(float lenght)
{
  GLboolean depth;
  glGetBooleanv(GL_DEPTH_TEST, &depth);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glVertex3f(    0.0, 0.0, 0.0);
  glVertex3f( lenght, 0.0, 0.0);

  glColor4f(0.0, 1.0, 0.0, 1.0);
  glVertex3f( 0.0,    0.0, 0.0);
  glVertex3f( 0.0, lenght, 0.0);

  glColor4f(0.0, 0.0, 1.0, 1.0);
  glVertex3f( 0.0, 0.0,    0.0);
  glVertex3f( 0.0, 0.0, lenght);
  glEnd();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  if(depth==false)
    {
    glDisable(GL_DEPTH_TEST);
    }

}

void GlutViewController::drawModel(ModelLoader model)
{
  TRIANGLE triangle;
  glBegin(GL_TRIANGLES);
  for(int j=0; j<model.getNumberOfData(); j++){
    model.getDataAtIndex(j, &triangle);
    glNormal3fv(triangle.normal);
    for(int i=0; i<3; i++)
      glVertex3fv(triangle.vertex[i]);
    }
  glEnd();
}

void GlutViewController::mouse(int button, int state, int x, int y)
{
  //printf("MousePress: button: %d, state: %d, x: %d, y: %d\n", button, state, x, y);
  mouseState.button = button;
  mouseState.pressed = ~state;
  mouseState.x = x;
  mouseState.y = y;

  if (button == 3)
    {
    camera.distance *= 0.875;
    }
  else if (button == 4)
    {
    camera.distance *= 1.125;
    }
}

void GlutViewController::motion(int x, int y)
{
  int moved_x = x - mouseState.x;
  int moved_y = y - mouseState.y;
  if (mouseState.button == 0 && mouseState.pressed)
    {
    incrimentCameraAngle(moved_x/100.0, moved_y/100.0);
    }
  else if (mouseState.button == 2 && mouseState.pressed)
    {
    moveLookAtPoint(moved_x, moved_y);
    }
  mouseState.x = x;
  mouseState.y = y;
}

void GlutViewController::mouseWheel(int wheel, int direction, int x, int y)
{
  if(direction==1){
    camera.distance *= 1.125;
    }else{
    camera.distance *= 0.875;
    }
}

void GlutViewController::incrimentCameraAngle(float dPan, float dTilt)
{
  camera.pan += dPan;
  camera.tilt += dTilt;
  if (camera.tilt >= M_PI / 2.0) camera.tilt = M_PI / 2.0 - 0.001;
  else if (camera.tilt <= -M_PI / 2.0) camera.tilt = - (M_PI / 2.0 - 0.001);
}

void GlutViewController::moveLookAtPoint(int dx, int dy)
{
  //TODO Consider camera distance
  camera.lock_x -= camera.distance * 0.0011 * (dx * cos(camera.pan) + dy*sin(camera.tilt)*sin(camera.pan));
  camera.lock_y += camera.distance * 0.0011 * (dy * cos(camera.tilt));
  camera.lock_z += camera.distance * 0.0011 * (dx * sin(camera.pan) - dy*sin(camera.tilt)*cos(camera.pan));
}

void GlutViewController::overlayDispray(char *string, int x, int y)
{
  //TODO right-aligned and buttom-aligned
  char buf[128];
  strcpy(buf, "\n");
  strcat(buf, string);

  glColor3f(0.0, 0.0, 0.0);

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(	0.0, 2.0, 2.0, 0.0, -1.0, 1.0 );
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushAttrib(GL_ENABLE_BIT );
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_CULL_FACE );

  glRasterPos3f( x, y, 0.0 );
  glutBitmapString( GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(buf) );

  glPopAttrib();
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

} //namespace glutCppWrapper
