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
	if (++objCounter == 1)
	{
		front = new ObjMesh("front.obj");
		back = new ObjMesh("back.obj");
		screen = new ObjMesh("screen.obj");
		keys = new ObjMesh("keys.obj");
		antenna = new ObjMesh("antenna.obj");
		board = new ObjMesh("board.obj");
		chip = new ObjMesh("chip.obj");
	}
	CurrentState = State;
}


Mobile::~Mobile()
{
	if (--objCounter == 0)
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
	if (CurrentState & Back)
	{
		glColor4fv(colors[0]);
		back->Render();
	}
	if (CurrentState & Front) 
	{ 
		glColor4fv(colors[1]);
		front->Render();
	}
	if (CurrentState & Board)
	{
		glColor4fv(colors[2]);
		board->Render();
	}
	if (CurrentState & Chip) 
	{
		glColor4fv(colors[3]);
		chip->Render();
	}
	if (CurrentState & Screen)
	{ 
		glColor4fv(colors[4]);
		screen->Render();
	}
	if (CurrentState & Antenna) 
	{
		glColor4fv(colors[5]);
		antenna->Render();
	}
	if (CurrentState & Keys) 
	{
		glColor4fv(colors[6]);
		keys->Render();
	}
}

void Mobile::Process(float dt)
{

}