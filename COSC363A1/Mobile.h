#pragma once
#include "base_object.h"
#include "mesh.h"

class Mobile :
	public SceneObject
{
	static int objCounter;
	static ObjMesh *front;
	static ObjMesh *back;
	static ObjMesh *board;
	static ObjMesh *chip;
	static ObjMesh *screen;
	static ObjMesh *keys;
	static ObjMesh *antenna;

public: 
	enum state {
		Back = 0b00000001,
		Front = 0b00000010,
		Board = 0b00000100,
		Chip = 0b00001000,
		Screen = 0b00010000,
		Antenna = 0b00100000,
		Keys = 0b01000000,
		BoardChip = Board | Chip,
		BoardChipScreen = BoardChip | Screen,
		BackAndBoard = Back | BoardChipScreen,
		BackAssembly = BackAndBoard | Antenna,
		FrontAssembly = Front | Keys,
		Full = FrontAssembly | BackAssembly
	};
	float colors[7][4] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.9f, 0.9f, 0.9f, 1.0f,
		0.2f, 1.0f, 0.2f, 1.0f,
		0.2f, 0.2f, 0.2f, 1.0f,
		0.6f, 0.7f, 0.6f, 1.0f,
		0.1f, 0.1f, 0.1f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
	};
private:
	state CurrentState;
public:
	Mobile(state State);
	~Mobile();
	Mobile Combine(Mobile combinand);
	virtual void Render();
	virtual void Process(float dt);
};

