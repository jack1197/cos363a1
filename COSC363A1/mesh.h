#pragma once
#include "base_object.h"
#include <vector>
#include <array>
#include <string>


class ObjMesh : public SceneObject
{
    float color[4];
    std::vector<float*> verticies;
    std::vector<int*> faces;
public:
    ObjMesh(std::string fileName, float color[4]);
    ~ObjMesh();
    virtual void Render();
    virtual void Process(float dt);
};