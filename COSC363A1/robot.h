#pragma once
#include "base_object.h"
class Robot :
	public SceneObject
{
	const float axisHeight = 2.8; //determined by the height of the first arms axis of rotation above 0
	float coreAngle = 30;
	float armAngle1 = 50;
	float armLength1 = 7;
	float armAngle2 = 40;
	float armLength2 = 7;
	float currentSetAngles[3]  = {0,0,0};
public:
	Robot();
	~Robot();
	virtual void Render();
	virtual void Process(double dt);
	void setAngles(float core, float arm1, float arm2);
	void setPos(float x, float y, float z);
};

