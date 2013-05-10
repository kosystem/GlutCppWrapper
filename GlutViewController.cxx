#include "GlutViewController.h"

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
		//TODO opacity
		glColor4f(1.0, 1.0, 1.0, 0.5);
		glutSolidTeapot(50);
		drawAxis(100);

		glPushMatrix();
		glTranslated(camera.lock_x, camera.lock_y, camera.lock_z);
		drawAxis(10);
		glPopMatrix();

		//TODO Add overlay display
	}


	void GlutViewController::drawAxis(float lenght)
	{
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
		camera.lock_x -= dx * cos(camera.pan) + dy*sin(camera.tilt)*sin(camera.pan);
		camera.lock_y += dy * cos(camera.tilt);
		camera.lock_z += dx * sin(camera.pan) - dy*sin(camera.tilt)*cos(camera.pan);
	}
}
