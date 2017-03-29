#pragma once
#include "base_object.h"
#include "texture.h"
#include "conveyor.h"
#include "robot.h"
#include "mesh.h"

class Factory :
	public SceneObject
{
	Texture *floorTex, *wallTex;
	Conveyor *conveyor;
	Robot *robot1;
	void concreteFloor(int subdivisions, int repetitions);
	void brickWall(int subdivisions, int repetitions);
	void subdividedSurface(int subdivisions, int repetitions, float v_stretch);
	ObjMesh *thing;
	ObjMesh *thing1;
	ObjMesh *thing2;
	ObjMesh *thing3;
	ObjMesh *thing4;
	ObjMesh *thing5;
	ObjMesh *thing6;

public:
	Factory();
	~Factory();
	virtual void Render();
	virtual void Process(double dt);
};

