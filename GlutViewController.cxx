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
		glutSolidTeapot(50);
		drawAxis(100);

		glPushMatrix();
		glTranslated(camera.lock_x, camera.lock_y, camera.lock_z);
		drawAxis(10);
		glPopMatrix();
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
		printf("MousePress: button: %d, state: %d, x: %d, y: %d\n", button, state, x, y);
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
			camera.pan += moved_x/100.0;
			camera.tilt += moved_y/100.0;
			if (camera.tilt >= M_PI / 2.0) camera.tilt = M_PI / 2.0 - 0.001;
			else if (camera.tilt <= -M_PI / 2.0) camera.tilt = - (M_PI / 2.0 - 0.001);
			}
		else if (mouseState.button == 2 && mouseState.pressed)
			{
			// TODO Consider direction of camera
			camera.lock_x += moved_x;
			camera.lock_y += moved_y;
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
}
