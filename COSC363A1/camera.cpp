#include "common.h"
#include "camera.h"

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
	float camHrizAngleTime = 0.0f;
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
		gluLookAt(MyCamera::camCurrentPosition[0], MyCamera::camCurrentPosition[1], MyCamera::camCurrentPosition[2],
		MyCamera::camCurrentPosition[0], MyCamera::camCurrentPosition[1], MyCamera::camCurrentPosition[2]-1,
		MyCamera::camCurrentUp[0], MyCamera::camCurrentUp[1], MyCamera::camCurrentUp[2]);
		glRotatef(-MyCamera::camCurrentAngle[1], 0,1,0);
		glRotatef(MyCamera::camCurrentAngle[0], 1,0,0);
	}

}

void camTargeted(bool target)
{

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