#include "common.h"
#include "handlers.h"
#include "camera.h"
#include "keyboard.h"

void registerHandlers()
{
	glutSpecialFunc(specialPressed);
	glutSpecialUpFunc(specialReleased);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutTimerFunc(1)
}