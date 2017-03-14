#include "common.h"
#include "handlers.h"
#include "camera.h"

void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) camSetTarget(0, 2, 0, 0, 1);
	else if (key == GLUT_KEY_DOWN) camSetTarget(0, -2, 0, 0, 1);
	else if (key == GLUT_KEY_LEFT) camSetTarget(2, 0, 0, 0, 1);
	else if (key == GLUT_KEY_RIGHT) camSetTarget(-2, 0, 0, 0, 1);
	glutPostRedisplay();
}

void registerHandlers()
{
	glutSpecialFunc(special);
}