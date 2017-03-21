#include "factory.h"
#include "common.h"


Factory::Factory()
{
	floorTex = new Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga", "TGA");
	wallTex = new Texture("TexturesCom_BrickSmallBrown0270_1_seamless_S.tga", "TGA");
}


Factory::~Factory()
{
	delete floorTex;
	delete wallTex;
}

void Factory::Render()
{
	glPushMatrix();
	glScalef(100, 1, 100);
	glTranslatef(-0.5f, 0.f, -0.5f);
	concreteFloor(10, 3);
	glPopMatrix();

	glPushMatrix();
	for(int i= 0; i<4; i++)
	{
		glPushMatrix();
		glTranslatef(0, 12.5, -50);
		glRotatef(90, 1, 0, 0);
		glScalef(100, 1, 25);
		glTranslatef(-0.5, 0, -0.5);
		brickWall(10, 6);
		glPopMatrix();
		glRotatef(90, 0, 1, 0);
	}
	glPopMatrix();
}

void Factory::Process(double dt)
{

}

void Factory::brickWall(int subdivisions, int repetitions)
{
	wallTex->bind();
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	subdividedSurface(subdivisions, repetitions, 0.25);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Factory::concreteFloor(int subdivisions, int repetitions)
{
	floorTex->bind();
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	subdividedSurface(subdivisions, repetitions, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Factory::subdividedSurface(int subdivisions, int repetitions, float v_stretch)
{
	for (int i = 0; i < subdivisions; i++)
		for (int j = 0; j < subdivisions; j++)
		{
			float x1 = (float)i / (float)(subdivisions);
			float x2 = (float)(i + 1) / (float)(subdivisions);
			float y1 = (float)j / (float)(subdivisions);
			float y2 = (float)(j + 1) / (float)(subdivisions);
			glNormal3f(0.f, 1.f, 0.f);
			glTexCoord2f(x1*repetitions, y1*repetitions*v_stretch);
			glVertex3f(x1, 0.f, y1);
			glTexCoord2f(x1*repetitions, y2*repetitions*v_stretch);
			glVertex3f(x1, 0.f, y2);
			glTexCoord2f(x2*repetitions, y2*repetitions*v_stretch);
			glVertex3f(x2, 0.f, y2);
			glTexCoord2f(x2*repetitions, y1*repetitions*v_stretch);
			glVertex3f(x2, 0.f, y1);
		}
}