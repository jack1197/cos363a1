#pragma once
#include "base_object.h"
#include "texture.h"
#include "conveyor.h"
#include "robot.h"
#include "Mobile.h"
#include <random>

class Factory :
	public SceneObject
{
	Texture *floorTex, *wallTex;
	Conveyor *conveyor;
	Conveyor *conveyor2;
	Robot *robot1;
	Robot *robot2;
	Robot *robot3;
	Robot *robot4;
	Robot *robot5;
	Robot *robot6;
	Robot *robotb1;
	Robot *robotb2;
	Robot *robotb3;
	void concreteFloor(int subdivisions, int repetitions);
	void brickWall(int subdivisions, int repetitions);
	void subdividedSurface(int subdivisions, int repetitions, float v_stretch);
	const static int mobilesOnBelt = 6;
	const static int mobilesOnBelt2 = 5;
	Mobile *mobiles[mobilesOnBelt];
	Mobile *mobiles2[mobilesOnBelt2];
	float cyclepos = 0.0f;
	float cyclelen = 5.0f;
	float robotOffsets[6] = { -0.2f, -0.34f, -0.2f, -0.45f, -0.4f, -0.45f };
	float robotOffsets2[3] = { -0.15f, -0.2f, -0.35f };
	float colorMins[8][4] = {
		{0.f, 0.f,0.f,1.f},
		{0},
		{0.f, 0.f,0.f,1.f},
		{0.f, 0.f,0.f,1.f},
		{0.f, 0.f,0.f,1.f},
		{0.f, .8f,0.f,1.f},
		{0.f, 0.f,0.f,1.f},
		{.7f, .85f,.7f,1.f}
	};
	float colorMaxs[8][4] = {
		{1.f, 1.f,1.f,1.f},
		{0},
		{1.f, 1.f,1.f,1.f},
		{1.f, 1.f,1.f,1.f},
		{1.f, 1.f,1.f,1.f},
		{.2f, 1.f,.2f,1.f},
		{.2f, .2f,.2f,1.f},
		{.85f, 1.f,.85f,1.f}
	};
	std::default_random_engine generator;
	std::uniform_real_distribution<float> randomDist = std::uniform_real_distribution<float>(0.0, 1.0);


public:
	Factory();
	~Factory();
	virtual void Render();
	virtual void Process(float dt);
};

