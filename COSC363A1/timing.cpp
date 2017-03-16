#include "common.h"
#include "timing.h"
#include "keyboard.h"
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

	std::cout<<isSpecialDown(GLUT_KEY_UP)<<"\n";

	glutPostRedisplay();
}
