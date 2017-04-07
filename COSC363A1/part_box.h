#pragma once
#include "base_object.h"
#include "common.h"

class PartBox :
	public SceneObject
{
public:
	PartBox();
	~PartBox();
	virtual void Render();
	virtual void Process(float dt);
};

