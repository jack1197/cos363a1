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
	glTranslatef(-0.5, 0, -0.5);
	concreteFloor(100, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,25,-50);
    glRotatef(90, 1, 0, 0);
	glScalef(100, 1, 50);
	glTranslatef(-0.5, 0, -0.5);
	brickWall(100, 3);
    glPopMatrix();
}

void Factory::Process(double dt)
{

}

void Factory::brickWall(int subdivisions, int repetitions)
{
    wallTex->bind();
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
	subdividedSurface(subdivisions, repetitions);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Factory::concreteFloor(int subdivisions, int repetitions)
{
    floorTex->bind();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	subdividedSurface(subdivisions, repetitions);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Factory::subdividedSurface(int subdivisions, int repetitions)
{
for (int i = 0; i < subdivisions; i++)
		for (int j = 0; j < subdivisions; j++)
		{
			float x1 = (float)i / (float)(subdivisions + 1);
			float x2 = (float)(i+1) / (float)(subdivisions + 1);
			float y1 = (float)j / (float)(subdivisions + 1);
			float y2 = (float)(j+1) / (float)(subdivisions + 1);
			glNormal3f(0, 1, 0);
			glTexCoord2f(x1*repetitions, y1*repetitions);
			glVertex3f(x1, 0, y1);
			glTexCoord2f(x1*repetitions, y2*repetitions);
			glVertex3f(x1, 0, y2);
			glTexCoord2f(x2*repetitions, y2*repetitions);
			glVertex3f(x2, 0, y2);
			glTexCoord2f(x2*repetitions, y1*repetitions);
			glVertex3f(x2, 0, y1);
		}
}