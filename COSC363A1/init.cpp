#include "common.h"
#include "init.h"
#include "camera.h"
#include "loadTGA.h"
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

	camSetPos(20, 20, 20);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10000);  //The camera view volume  


	//TODO: Move
	GLuint txId;
	glGenTextures(1, &txId);
	glBindTexture(GL_TEXTURE_2D, txId);
	loadTGA("TexturesCom_ConcreteBare0433_11_seamless_S.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}
