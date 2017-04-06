#include "Mobile.h"
#include "common.h"

int Mobile::objCounter = 0;
ObjMesh *Mobile::front = nullptr;
ObjMesh *Mobile::back = nullptr;
ObjMesh *Mobile::board = nullptr;
ObjMesh *Mobile::chip = nullptr;
ObjMesh *Mobile::screen = nullptr;
ObjMesh *Mobile::keys = nullptr;
ObjMesh *Mobile::antenna = nullptr;

Mobile::Mobile(state State)
{
	++objCounter;
	if (objCounter == 1)
	{
		front = new ObjMesh("front.obj");
		back = new ObjMesh("back.obj");
		screen = new ObjMesh("screen.obj");
		keys = new ObjMesh("keys.obj");
		antenna = new ObjMesh("antenna.obj");
		board = new ObjMesh("board.obj");
		chip = new ObjMesh("chip.obj");
		front->Optimize();
		back->Optimize();
		screen->Optimize();
		keys->Optimize();
		antenna->Optimize();
		board->Optimize();
		chip->Optimize();
	}
	CurrentState = State;
}


Mobile::~Mobile()
{
	--objCounter;
	if (objCounter == 0)
	{
		delete front;
		delete back;
		delete screen;
		delete keys;
		delete antenna;
		delete board;
		delete chip;
	}
}


void Mobile::Render()
{
	float spec_colour[3] = { .3f, .3f, .3f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2);
	glPushMatrix();
	glScalef(1, 1, 1);
	state baseStates[] = { Back,Front,  Board, Chip, Screen, Antenna, Keys };
	ObjMesh *mesh[] = { back, front, board, chip, screen, antenna, keys };
	for (int i = 0; i < 7; i++)
	{
		if (CurrentState & baseStates[i])
		{
			glColor4fv(colors[i]);
			mesh[i]->Render();
		}
	}
	glPopMatrix();
}

void Mobile::Process(float dt)
{

}

Mobile *Mobile::Combine(Mobile *combinand)
{

	Mobile *combination = new Mobile(state(CurrentState | combinand->CurrentState));
	state baseStates[] = { Back,Front,  Board, Chip, Screen, Antenna, Keys };
	for (int i = 0; i < 7; i++)
	{
		if (CurrentState & baseStates[i])
			memcpy(combination->colors[i], colors[i], sizeof(float) * 4);
		else
			memcpy(combination->colors[i], combinand->colors[i], sizeof(float) * 4);
	}
	return combination;
}