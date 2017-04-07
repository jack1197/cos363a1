#pragma once
#include "base_object.h"
#include "common.h"
#include "texture.h"

class PartBox :
	public SceneObject
{
	static int objCount;
	static Texture *cardboardTex;
public:
	PartBox();
	~PartBox();
	virtual void Render();
	virtual void Process(float dt);
};

