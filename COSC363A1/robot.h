#pragma once
#include "base_object.h"
class Robot :
	public SceneObject
{
	float armAngle1 = 0;
	float armAngle2 = 0;
	float coreAngle = 0;
public:
	Robot();
	~Robot();
	virtual void Render();
	virtual void Process(double dt);
	void setAngles(float core, float arm1, float arm2);
};

