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
	const static int mobilesOnBelt = 7;
	Mobile *mobiles[mobilesOnBelt];
	float cyclepos = 0.0f;
	float cyclelen = 5.0f;

public:
	Factory();
	~Factory();
	virtual void Render();
	virtual void Process(float dt);
};

