#include "common.h"
#include "timing.h"
#include "keyboard.h"
#include "camera.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;
namespace myTiming
{
	high_resolution_clock::time_point last;
	high_resolution_clock::time_point start;
}

void timerInit()
{
	myTiming::last = high_resolution_clock::now();
	myTiming::start = high_resolution_clock::now();
}

void frameProcesses(int number)
{
	high_resolution_clock::time_point now = high_resolution_clock::now();
	double dt = duration_cast<duration<double>>(now - myTiming::last).count();
	myTiming::last = now;
	std::cout << dt << "\t"<<1./dt<<"\n";

	camSmoothingStep(dt);
	cameraProcesses(dt);


	glutPostRedisplay();
}

void cameraProcesses(float dt)
{
	const float unitsPerSec = 20;
	if(isSpecialDown(GLUT_KEY_UP))
	{
		camSetPos(0, unitsPerSec*dt, 0, 1, 1);
	}
	if(isSpecialDown(GLUT_KEY_DOWN))
	{
		camSetPos(0, -unitsPerSec*dt, 0, 1, 1);
	}
	if(isSpecialDown(GLUT_KEY_LEFT))
	{
		camSetPos( -unitsPerSec*dt,0,  0, 1, 1);
	}
	if(isSpecialDown(GLUT_KEY_RIGHT))
	{
		camSetPos(unitsPerSec*dt,0, 0, 1, 1);
	}
}
