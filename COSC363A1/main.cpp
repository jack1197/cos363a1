/*
COSC363 17S1 Assignment 1 - A Robot's World
*/

#include "common.h"
#include "init.h"
#include "display.h"
#include "handlers.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("COSC363 Ass1 - A Robots World");
	initialize();

	glutDisplayFunc(render);
	registerHandlers();
	glutMainLoop();
	return 0;
}
