#include "factory.h"
#include "common.h"

Factory::Factory()
{
    floorTex = new Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga", "TGA");
    wallTex = new Texture("TexturesCom_BrickSmallBrown0270_1_seamless_S.tga", "TGA");
    conveyor = new Conveyor();
	robot1 = new Robot(7,7);
	float color[4] = {.8,.8,.8,1.};
	thing = new ObjMesh("front.obj" , color);
	thing1 = new ObjMesh("back.obj" , color);
	thing2 = new ObjMesh("screen.obj" , color);
	thing3 = new ObjMesh("keys.obj" , color);
	thing4 = new ObjMesh("antenna.obj" , color);
	thing5 = new ObjMesh("board.obj" , color);
	thing6 = new ObjMesh("chip.obj" , color);
}

Factory::~Factory()
{
    delete floorTex;
    delete wallTex;
	delete conveyor;
	delete robot1;
}

void Factory::Render()
{
    glPushMatrix();
    glScalef(100, 1, 100);
    glTranslatef(-0.5f, 0.f, -0.5f);
    concreteFloor(100, 3);
    glPopMatrix();

    glPushMatrix();
    for (int i = 0; i < 4; i++)
    {
		
	glPushMatrix();
	glTranslatef(0, 12.5, -50);
	glRotatef(90, 1, 0, 0);
	glScalef(100, 1, 25);
	glTranslatef(-0.5, 0, -0.5);
	brickWall(100, 10);
	glPopMatrix();
	glRotatef(90, 0, 1, 0);
    }
    glPopMatrix();
	
    glPushMatrix();
    glTranslatef(19.5, 0, 0);
    conveyor->Render();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-19, 0, 0);
    conveyor->Render();
    glPopMatrix();
	
    glPushMatrix();
    glTranslatef(0,7,5.5);
	robot1->Render();
    glPopMatrix();

    thing->Render();
    thing1->Render();
    thing2->Render();
    thing3->Render();
    thing4->Render();
    thing5->Render();
    thing6->Render();
}

void Factory::Process(double dt)
{
    conveyor->Process(dt);
    robot1->Process(dt);
}

void Factory::brickWall(int subdivisions, int repetitions)
{
	float spec_colour[3] = {.1f, .1f, .1f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2); 
    wallTex->bind();
    glColor3f(1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
    subdividedSurface(subdivisions, repetitions, 0.25);
    glDisable(GL_TEXTURE_2D);
}

void Factory::concreteFloor(int subdivisions, int repetitions)
{
	float spec_colour[3] = {.6f, .6f, .6f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2); 
    floorTex->bind();
    glColor3f(1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
    subdividedSurface(subdivisions, repetitions, 1);
    glDisable(GL_TEXTURE_2D);
}

void Factory::subdividedSurface(int subdivisions, int repetitions, float v_stretch)
{
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    for (int i = 0; i < subdivisions; i++)
	for (int j = 0; j < subdivisions; j++)
	{
	    float x1 = (float)i / (float)(subdivisions);
	    float x2 = (float)(i + 1) / (float)(subdivisions);
	    float y1 = (float)j / (float)(subdivisions);
	    float y2 = (float)(j + 1) / (float)(subdivisions);
	    glNormal3f(0.f, 1.f, 0.f);
	    glTexCoord2f(x1 * repetitions, y1 * repetitions * v_stretch);
	    glVertex3f(x1, 0.f, y1);
	    glTexCoord2f(x1 * repetitions, y2 * repetitions * v_stretch);
	    glVertex3f(x1, 0.f, y2);
	    glTexCoord2f(x2 * repetitions, y2 * repetitions * v_stretch);
	    glVertex3f(x2, 0.f, y2);
	    glTexCoord2f(x2 * repetitions, y1 * repetitions * v_stretch);
	    glVertex3f(x2, 0.f, y1);
	}
    glEnd();
}