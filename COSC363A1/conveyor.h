#pragma once
#include "base_object.h"
class Conveyor :
	public SceneObject
{
	void Frame();
public:
	Conveyor();
	~Conveyor();
	virtual void Render();
	virtual void Process(double dt);
};

