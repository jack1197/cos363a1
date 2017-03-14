#include "common.h"
#include "display.h"
#include "camera.h"
/*
Render frame
*/
void render()
{
	//Setup frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cameraMatrix();

	float lightpos[3] = { -20.f, 20.f, 20.f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glColor3f(1, 0, 0);
	glutSolidCube(1);
	//update screen
	glutSwapBuffers();
}