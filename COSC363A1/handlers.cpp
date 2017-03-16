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
	timerInit();
}