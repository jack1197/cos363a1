#pragma once

namespace myTiming
{
	extern bool freeLook;
}

void timerInit();
void frameProcesses(int number);
void cameraProcesses(float dt);