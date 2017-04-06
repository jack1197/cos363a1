#pragma once
#include "base_object.h"
#include "mesh.h"

class Robot :
	public SceneObject
{
	const float axisHeight = 2.8f; //determined by the height of the first arms axis of rotation above 0
	float coreAngle = 0;
	float coreAngleTarget = 0;
	float armAngle1 = 0;
	float armAngle1Target = 0;
	float armLength1;
	float armAngle2 = 0;
	float armAngle2Target = 0;
	float armLength2;
	double time = 0;
	void movementStep(float dt);
public:
	SceneObject *attached = nullptr;
	float attachedOffset[3] = {0,0,0};
	bool attachFlipped = false;
	Robot(float armLength1, float armLength2);
	~Robot();
	virtual void Render();
	virtual void Process(float dt);
	void setAngles(float core, float arm1, float arm2);
	void setPos(float x, float y, float z);
};

