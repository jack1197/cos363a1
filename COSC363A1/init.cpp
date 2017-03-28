#include "common.h"
#include "init.h"
#include "camera.h"
#include "texture.h"
#include "factory.h"
#include "display.h"
/*
Initialise frame
*/
void initialize()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camSetPos(0.f, 20.f, 20.f);
	camSetAngle(30,-20,1,0);
	camTargeted(false);

	Factory *fact = new Factory();
	setRootObj(fact);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, .01, 10000);  //The camera view volume  

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}
