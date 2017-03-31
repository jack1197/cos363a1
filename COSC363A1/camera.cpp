#include "common.h"
#include "camera.h"
#include <cmath>

namespace MyCamera
{
	float camCurrentPosition[3] = { 0,0,0 };
	float camSetPosition[3] = { 0,0,0 };
	float camCurrentTarget[3] = { 0,0,0 };
	float camSetTarget[3] = { 0,0,0 };
	float camCurrentUp[3] = { 0,1,0 };
	float camSetUp[3] = { 0,1,0 };
	float camCurrentAngle[2] = {0, 0};
	float camSetAngle[2] = {0, 0};
	float camTargetTime = 0.0f;
	float camPosTime = 0.0f;
	float camUpTime = 0.0f;
	float camVertAngleTime = 0.0f;
	float camHorizAngleTime = 0.0f;
	bool targetMode = true;
}

void cameraMatrix()
{
	if (MyCamera::targetMode)
	{
		gluLookAt(MyCamera::camCurrentPosition[0], MyCamera::camCurrentPosition[1], MyCamera::camCurrentPosition[2], 
			MyCamera::camCurrentTarget[0], MyCamera::camCurrentTarget[1], MyCamera::camCurrentTarget[2], 
			MyCamera::camCurrentUp[0], MyCamera::camCurrentUp[1], MyCamera::camCurrentUp[2]);
	}
	else
	{
		glRotatef(-MyCamera::camCurrentAngle[1], 1,0,0);
		glRotatef(MyCamera::camCurrentAngle[0], 0,1,0);
		gluLookAt(MyCamera::camCurrentPosition[0], MyCamera::camCurrentPosition[1], MyCamera::camCurrentPosition[2],
		MyCamera::camCurrentPosition[0], MyCamera::camCurrentPosition[1], MyCamera::camCurrentPosition[2]-1,
		MyCamera::camCurrentUp[0], MyCamera::camCurrentUp[1], MyCamera::camCurrentUp[2]);
	}

}

void camTargeted(bool target)
{
	MyCamera::targetMode = target;
}

/*
set current camera target
*/
void camSetTarget(float point[3], bool snap, bool relative)
{

	if (relative)
	{
		for (int i = 0; i < 3; i++)
			MyCamera::camSetTarget[i] += point[i];
	}
	else
	{
		memcpy(MyCamera::camSetTarget, point, 3 * sizeof(float));
	}
	if (snap || MyCamera::camPosTime == 0.0f)
	{
		memcpy(MyCamera::camCurrentTarget, MyCamera::camSetTarget, 3*sizeof(float));
	}
}

/*
set current camera position
*/
void camSetPos(float point[3], bool snap, bool relative)
{
	if (relative)
	{
		for (int i = 0;i < 3; i++)
			MyCamera::camSetPosition[i] += point[i];
	}
	else
	{
		memcpy(MyCamera::camSetPosition,point, 3 * sizeof(float));
	}
	if (snap || MyCamera::camPosTime == 0.0f)
	{
		memcpy(MyCamera::camCurrentPosition, MyCamera::camSetPosition, 3 * sizeof(float));
	}
}

/*
set current camera up vector
*/
void camSetUp(float vector[3], bool snap, bool relative)
{
	if (relative)
	{
		for (int i = 0; i < 3; i++)
			MyCamera::camSetUp[i] += vector[i];
	}
	else
	{
		memcpy(MyCamera::camSetUp, vector, 3 * sizeof(float));
	}
	if (snap || MyCamera::camUpTime == 0.0f)
	{
		memcpy(MyCamera::camCurrentUp, MyCamera::camSetUp, 3 * sizeof(float));
	}
}

void camSetAngle(float azimuth, float elevation, bool snap, bool relative)
{
	if (relative)
	{
		MyCamera::camSetAngle[0] += azimuth;
		MyCamera::camSetAngle[1] += elevation;
	}
	else
	{
		MyCamera::camSetAngle[0] = azimuth;
		MyCamera::camSetAngle[1] = elevation;
	}
	if (MyCamera::camSetAngle[1] > 90.f) MyCamera::camSetAngle[1] = 90.f;
	if (MyCamera::camSetAngle[1] < -90.f) MyCamera::camSetAngle[1] = -90.f;
	if (snap || MyCamera::camHorizAngleTime == 0.0f)
	{
		MyCamera::camCurrentAngle[0] = MyCamera::camSetAngle[0];
	}
	if (snap || MyCamera::camVertAngleTime == 0.0f)
	{
		MyCamera::camCurrentAngle[1] = MyCamera::camSetAngle[1];
	}
}

void camSetTarget(float x, float y, float z, bool snap, bool relative)
{
	float vec[3] = { x,y,z };
	camSetTarget(vec, snap, relative);
}

void camSetPos(float x, float y, float z, bool snap, bool relative)
{
	float vec[3] = { x,y,z };
	camSetPos(vec, snap, relative);
}
void camSetUp(float x, float y, float z, bool snap, bool relative)
{
	float vec[3] = { x,y,z };
	camSetUp(vec, snap, relative);
}
/*
set smoothing times
*/
void camSetSmoothing(float targetTime, float posTime, float upTime) 
{
	MyCamera::camTargetTime = targetTime;
	MyCamera::camPosTime = posTime;
	MyCamera::camUpTime = upTime;
}

/*
run smoothing step each frame
*/
void camSmoothingStep(float dt)
{
	//TODO:Actually make smooth
	memcpy(MyCamera::camSetPosition, MyCamera::camCurrentPosition, 3 * sizeof(float));
	memcpy(MyCamera::camSetTarget, MyCamera::camCurrentTarget, 3 * sizeof(float));
	memcpy(MyCamera::camSetUp, MyCamera::camCurrentUp, 3 * sizeof(float));
}
void camGetAngles(float output[2])
{
	output[0] = MyCamera::camSetAngle[0];
	output[1] = MyCamera::camSetAngle[1];
}

void camGetDirection(float output[3])
{
	camGetDirection(output, MyCamera::targetMode);
}


void camGetDirection(float output[3], bool targetMode)
{
	output[0] = sin(MyCamera::camSetAngle[0]/180.f*PI) * cos(MyCamera::camSetAngle[1]/180.f*PI);
	output[1] = sin(MyCamera::camSetAngle[1]/180.f*PI);
	output[2] = -cos(MyCamera::camSetAngle[0]/180.f*PI) * cos(MyCamera::camSetAngle[1]/180.f*PI);
}