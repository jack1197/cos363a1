#include "common.h"
#include "handlers.h"
#include "camera.h"
#include "keyboard.h"
#include "timing.h"
#include <iostream>
#include <chrono>

void registerHandlers()
{
	glutSpecialFunc(specialPressed);
	glutSpecialUpFunc(specialReleased);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutReshapeFunc(reshaped);
	timerInit();
}

void reshaped(int w, int h)
{
	//glutReshapeWindow(w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(w)/h, .01f, 10000);  //The camera view volume  
}