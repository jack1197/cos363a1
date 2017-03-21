#pragma once
#include "base_object.h"
#include "texture.h"
class Factory :
	public SceneObject
{
	Texture *floorTex, *wallTex;
	void concreteFloor(int subdivisions, int repetitions);
	void brickWall(int subdivisions, int repetitions);
	void subdividedSurface(int subdivisions, int repetitions, float v_stretch);

public:
	Factory();
	~Factory();
	virtual void Render();
	virtual void Process(double dt);
};

