#pragma once
#include "base_object.h"
#include <vector>
#include <array>
#include <string>


class ObjMesh : public SceneObject
{
	std::vector<float*> verticies;
	std::vector<int*> faces;
	float *optimized = nullptr;
	int n = 0;
public:
	ObjMesh(std::string fileName);
	~ObjMesh();
	virtual void Render();
	virtual void Process(float dt);
	void Optimize();
};