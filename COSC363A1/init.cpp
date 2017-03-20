#include "common.h"
#include "init.h"
#include "camera.h"
#include "texture.h"
/*
Initialise frame
*/
void initialize()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	camSetPos(20, 20, 20);
	camTargeted(false);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10000);  //The camera view volume  

	Texture floorTex = Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga");

}
