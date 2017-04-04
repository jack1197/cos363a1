#include "factory.h"
#include "common.h"

Factory::Factory()
{
	floorTex = new Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga", "TGA");
	wallTex = new Texture("TexturesCom_BrickSmallBrown0270_1_seamless_S.tga", "TGA");
	conveyor = new Conveyor();
	robot1 = new Robot(7, 7);

	for (int i = 0; i<mobilesOnBelt; i++)
	{
		mobiles[i] = new Mobile(Mobile::Full);
	}
	delete mobiles[0];
	mobiles[0] = new Mobile(Mobile::Full);

}

Factory::~Factory()
{
	delete floorTex;
	delete wallTex;
	delete conveyor;
	delete robot1;

	for (int i = 0; i<mobilesOnBelt; i++)
	{
		delete mobiles[i];
	}
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
		glTranslatef(0, 12.5f, -50);
		glRotatef(90, 1, 0, 0);
		glScalef(100, 1, 25);
		glTranslatef(-0.5f, 0, -0.5f);
		brickWall(100, 10);
		glPopMatrix();
		glRotatef(90, 0, 1, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(19.5f, 0, 0);
	conveyor->Render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-19, 0, 0);
	conveyor->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7, 5.5f);
	robot1->Render();
	glPopMatrix();

	for (int i = 0; i<mobilesOnBelt; i++)
	{
		glPushMatrix();
		glTranslatef(-40.0f+i*12+cyclepos*2.4f, 6.0f, 0);
		std::cout<<mobiles[i]<<"\n";
		mobiles[i]->Render();
		glPopMatrix();
	}

}

void Factory::Process(float dt)
{
	conveyor->Process(dt);

	robot1->Process(dt);

	cyclepos += dt;
	if (cyclepos > cyclelen)
	{
		cyclepos -= cyclelen;	
		delete mobiles[mobilesOnBelt-1];
		memcpy(&mobiles[1], mobiles, sizeof(void*)*(mobilesOnBelt-1));
		mobiles[0] = new Mobile(Mobile::BackAssembly);
		std::cout<<"3\n";
	}
}

void Factory::brickWall(int subdivisions, int repetitions)
{
	float spec_colour[3] = { .1f, .1f, .1f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2);
	wallTex->bind();
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	subdividedSurface(subdivisions, repetitions, 0.25f);
	glDisable(GL_TEXTURE_2D);
}

void Factory::concreteFloor(int subdivisions, int repetitions)
{
	float spec_colour[3] = { .6f, .6f, .6f };
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