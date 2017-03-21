#include "common.h"
#include "display.h"
#include "camera.h"
#include "timing.h"
#include "base_object.h"
/*
Render frame
*/
SceneObject *rootObj;

void render()
{
	//Setup frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cameraMatrix();

	float lightpos[4] = { -10.f, 50.f, 10.f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	rootObj->Render();
	//update screen
	glutSwapBuffers();
	glutTimerFunc(0, frameProcesses, 0);
}

void setRootObj(SceneObject *obj)
{
	rootObj = obj;
}