#pragma once
#include "base_object.h"
class Robot :
	public SceneObject
{
	const float axisHeight = 2.8; //determined by the height of the first arms axis of rotation above 0
	float coreAngle = 0;
	float coreAngleTarget = 0;
	float armAngle1 = 0;
	float armAngle1Target = 0;
	float armLength1;
	float armAngle2 = 0;
	float armAngle2Target = 0;
	float armLength2;
	double time = 0;
	void movementStep(double dt);
public:
	Robot(float armLength1, float armLength2);
	~Robot();
	virtual void Render();
	virtual void Process(double dt);
	void setAngles(float core, float arm1, float arm2);
	void setPos(float x, float y, float z);
};

