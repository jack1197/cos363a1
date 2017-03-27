#pragma once
#include "base_object.h"
class Robot :
	public SceneObject
{
	float armAngle1 = 50;
	float armLength1 = 7;
	float armAngle2 = 0;
	float armLength2 = 7;
	float coreAngle = 0;
public:
	Robot();
	~Robot();
	virtual void Render();
	virtual void Process(double dt);
	void setAngles(float core, float arm1, float arm2);
};

