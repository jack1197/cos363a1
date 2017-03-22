#pragma once
#include "base_object.h"
class Robot :
	public SceneObject
{
public:
	Robot();
	~Robot();
	virtual void Render();
	virtual void Process(double dt);
};

