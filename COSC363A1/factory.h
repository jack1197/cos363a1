#pragma once
#include "base_object.h"
#include "texture.h"
#include "conveyor.h"
#include "robot.h"
#include "Mobile.h"

class Factory :
	public SceneObject
{
	Texture *floorTex, *wallTex;
	Conveyor *conveyor;
	Robot *robot1;
	void concreteFloor(int subdivisions, int repetitions);
	void brickWall(int subdivisions, int repetitions);
	void subdividedSurface(int subdivisions, int repetitions, float v_stretch);
	Mobile *mobile;

public:
	Factory();
	~Factory();
	virtual void Render();
	virtual void Process(float dt);
};

