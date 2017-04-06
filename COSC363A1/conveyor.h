#pragma once
#include "base_object.h"
class Conveyor :
	public SceneObject
{
	float cycleProgress = 0;
	void Frame();
public:
	float cyclesPerSec = 2.f;
	Conveyor();
	~Conveyor();
	virtual void Render();
	virtual void Process(float dt);
};

