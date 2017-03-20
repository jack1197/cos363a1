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
	//std::cout << dt << "\t" << 1. / dt << "\n";

	camSmoothingStep(dt);
	cameraProcesses(dt);


	glutPostRedisplay();
}

void cameraProcesses(float dt)
{
	const float degPerSec = 30;
	const float unitPerSec = 10;


	float direction[3];
	camGetDirection(direction);
	float angles[2];
	camGetAngles(angles);
	if (isSpecialDown(GLUT_KEY_UP))
	{
		camSetAngle(0,degPerSec*dt, 1, 1);
	}
	if (isSpecialDown(GLUT_KEY_DOWN))
	{
		camSetAngle(0, -degPerSec*dt, 1, 1);

	}
	if (isSpecialDown(GLUT_KEY_LEFT))
	{
		camSetAngle(-degPerSec*dt, 0,1, 1);

	}
	if (isSpecialDown(GLUT_KEY_RIGHT))
	{
		camSetAngle(degPerSec*dt, 0,1, 1);
	}
	if (isKeyDown('w'))
	{
		float multiplied[3];
		for (int i = 0;i < 3; i++)
			multiplied[i] = direction[i] * unitPerSec * dt;
		camSetPos(multiplied, 1, 1);
	}
	if (isKeyDown('s'))
	{
		float multiplied[3];
		for (int i = 0;i < 3; i++)
			multiplied[i] = direction[i] * unitPerSec * dt * -1;
		camSetPos(multiplied, 1, 1);
	}
	if (isKeyDown('a'))
	{
		float multiplied[3];
		multiplied[0] = -cos(angles[0] / 180.*PI) * unitPerSec * dt;
		multiplied[2] = -sin(angles[0] / 180.*PI) * unitPerSec * dt;
		multiplied[1] = 0.f;
		camSetPos(multiplied, 1, 1);
	}
	if (isKeyDown('d'))
	{
		float multiplied[3];
		multiplied[0] = cos(angles[0] / 180.*PI) * unitPerSec * dt;
		multiplied[2] = sin(angles[0] / 180.*PI) * unitPerSec * dt;
		multiplied[1] = 0.f;
		camSetPos(multiplied, 1, 1);
	}
	if (isSpecialDown(GLUT_KEY_SHIFT_L))
	{
		float multiplied[3];
		multiplied[0] = -sin(angles[0] / 180.*PI) * sin(angles[1] / 180.*PI) * unitPerSec * dt;
		multiplied[2] = cos(angles[0] / 180.*PI) * sin(angles[1] / 180.*PI) * unitPerSec * dt;
		multiplied[1] = cos(angles[1] / 180.*PI) * unitPerSec * dt;
		camSetPos(multiplied, 1, 1);
	}
	if (isSpecialDown(GLUT_KEY_CTRL_L))
	{

		float multiplied[3];
		multiplied[0] = sin(angles[0] / 180.*PI) * sin(angles[1] / 180.*PI) * unitPerSec * dt;
		multiplied[2] = -cos(angles[0] / 180.*PI) * sin(angles[1] / 180.*PI) * unitPerSec * dt;
		multiplied[1] = -cos(angles[1] / 180.*PI) * unitPerSec * dt;
		camSetPos(multiplied, 1, 1);
	}
	std::cout << direction[0] << "\t" << direction[1] << "\t" << direction[2] << "\n";
}
