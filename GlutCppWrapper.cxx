#include "GlutCppWrapper.h"

namespace glutCppWrapper {

GlutCppWrapper *GlutCppWrapper::instance = NULL;


GlutCppWrapper::GlutCppWrapper()
{
  title = "Glut Cpp Wrapper framework";
  camera.lock_x = 0;
  camera.lock_y = 0;
  camera.lock_z = 0;
  camera.distance = 300;
  camera.pan = 0.0;
  camera.tilt = 0.0;
}

void GlutCppWrapper::startFramework(int argc, char *argv[]) {

  setInstance();

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow(title.c_str());

  // Function callbacks
  glutDisplayFunc(displayWrapper);
  glutReshapeFunc(reshapeWrapper);
  glutIdleFunc(idleWrapper);

  glutMouseFunc(mouseWrapper);
  glutMotionFunc(motionWrapper);
  glutPassiveMotionFunc(passiveMotionWrapper);
  glutMouseWheelFunc(mouseWheelWrapper) ;

  glutKeyboardFunc(keyboardWrapper);
  glutKeyboardUpFunc(keyboardUpWrapper);
  glutSpecialFunc(specialWrapper);
  glutSpecialUpFunc(specialUpWrapper);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  load();

  glutMainLoop();				// Start the main GLUT thread
}



void GlutCppWrapper::setInstance()
{
  instance = this;
}

void GlutCppWrapper::displayFramework()
{
  // Set background color
  glClearColor(0.9, 0.9, 1.0, 1.0);

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear once

  setupLights();
  setCamera();

  display();

  glutSwapBuffers();
}

void GlutCppWrapper::setCamera()
{
  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)width / (double)height, 0.5, FLT_MAX);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera.distance*sin(camera.pan)*cos(camera.tilt) + camera.lock_x,
            camera.distance*sin(camera.tilt) + camera.lock_y,
            camera.distance*cos(camera.pan)*cos(camera.tilt) + camera.lock_z,
            camera.lock_x, camera.lock_y, camera.lock_z,
            0.0, 1.0, 0.0);
}

void GlutCppWrapper::setupLights() {
  // TODO multi lights
  GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
  GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
  GLfloat ambient_light[] = { 0.8, 0.8, 0.8, 1.0 };

  glLightfv( GL_LIGHT0, GL_POSITION, light1_position );
  glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
  glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );

  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );
}

void GlutCppWrapper::load()
{
  //NOTE Model data load
}

void GlutCppWrapper::display()
{
  glutSolidTeapot(50);
}

void GlutCppWrapper::reshape(int width, int height)
{
  glViewport(0,0,(GLsizei)width,(GLsizei)height);
}

void GlutCppWrapper::idle()
{
  glutPostRedisplay();
}

void GlutCppWrapper::mouse(int button, int state, int x, int y)
{
  printf("MousePress: button: %d, state: %d, x: %d, y: %d\n", button, state, x, y);
}

void GlutCppWrapper::motion(int x, int y)
{
  printf("MouseMove: x: %d, y: %d\n", x, y);
}

void GlutCppWrapper::passiveMotion(int x, int y)
{

}

void GlutCppWrapper::mouseWheel(int wheel, int direction, int x, int y)
{

}


void GlutCppWrapper::keyboard(unsigned char key, int x, int y)
{
  printf( "KeyboardPress: %c \n", key );
}

void GlutCppWrapper::keyboardUp(unsigned char key, int x, int y)
{
  printf( "KeyboardUp: %c \n", key );
}

void GlutCppWrapper::special(int key, int x, int y)
{
  printf( "SpecialKeyboardPress: %c \n", key );
}

void GlutCppWrapper::specialUp(int key, int x, int y)
{
  printf( "SpecialKeyboardUp: %c \n", key );
}


void GlutCppWrapper::displayWrapper()
{
  instance->displayFramework(); // calls display(float) with time delta
}

void GlutCppWrapper::reshapeWrapper(int width, int height)
{
  instance->reshape(width, height);
}

void GlutCppWrapper::idleWrapper()
{
  instance->idle();
}

void GlutCppWrapper::mouseWrapper(int button, int state, int x, int y)
{
  instance->mouse(button, state, x, y);
}

void GlutCppWrapper::motionWrapper(int x, int y)
{
  instance->motion(x, y);
}

void GlutCppWrapper::passiveMotionWrapper(int x, int y)
{
  instance->passiveMotion(x, y);
}

void GlutCppWrapper::mouseWheelWrapper(int wheel, int direction, int x, int y)
{
  instance->mouseWheel(wheel, direction, x, y);
}

void GlutCppWrapper::keyboardWrapper(unsigned char key, int x, int y)
{
  instance->keyboard(key,x,y);
}

void GlutCppWrapper::keyboardUpWrapper(unsigned char key, int x, int y)
{
  instance->keyboardUp(key,x,y);
}

void GlutCppWrapper::specialWrapper(int key, int x, int y)
{
  instance->special(key,x,y);
}

void GlutCppWrapper::specialUpWrapper(int key, int x, int y)
{
  instance->specialUp(key,x,y);
}
}
