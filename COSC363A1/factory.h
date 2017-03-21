#pragma once
#include "base_object.h"
class Factory :
	public SceneObject
{
public:
	Factory();
	~Factory();
	void Render();
	void Process(double dt);
};

