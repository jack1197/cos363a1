#include "common.h"
#include "handlers.h"
#include "camera.h"

void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) camSetPos(0, 2, 0, 0, 1);
	else if (key == GLUT_KEY_DOWN) camSetPos(0, -2, 0, 0, 1);
	else if (key == GLUT_KEY_LEFT) camSetPos(2, 0, 0, 0, 1);
	else if (key == GLUT_KEY_RIGHT) camSetPos(-2, 0, 0, 0, 1);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
}

void registerHandlers()
{
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
}