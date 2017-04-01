#pragma once
class SceneObject {

public:
	virtual void Render();
	virtual void Process(float dt);
};