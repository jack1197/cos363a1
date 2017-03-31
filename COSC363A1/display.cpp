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

	float lightpos0[4] = { 25.f, 80.f, -25.f, 1.0f };
	float lightpos1[4] = { -25.f, 80.f, -25.f, 1.0f };
	float lightpos2[4] = { -25.f, 80.f, 25.f, 1.0f };
	float lightpos3[4] = { 25.f, 80.f, 25.f, 1.0f };
	float lightspec[4] = { 1.f, 1.f, 1.f, 1.f};
	float lightdiff[4] = { 1.f, 1.f, 1.f, 1.0f};
	float spotdir[3] = { 0.f, -1.f, 0.f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.03f);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightspec);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 4);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.03f);
	glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightspec);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightdiff);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotdir);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.03f);
	glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lightspec);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightdiff);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotdir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 4);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.03f);
	rootObj->Render();
	//update screen
	glutSwapBuffers();
	glutTimerFunc(0, frameProcesses, 0);
}

void setRootObj(SceneObject *obj)
{
	rootObj = obj;
}

SceneObject *getRootObj()
{
	return rootObj;
}