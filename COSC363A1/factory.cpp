#include "factory.h"
#include "common.h"

Factory::Factory()
{
	floorTex = new Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga", "TGA");
	wallTex = new Texture("TexturesCom_BrickSmallBrown0270_1_seamless_S.tga", "TGA");
	conveyor = new Conveyor();
	robot1 = new Robot(7, 7);
	robot2 = new Robot(7, 7);
	robot3 = new Robot(7, 7);
	robot4 = new Robot(7, 7);
	robot5 = new Robot(7, 7);

	mobiles[0] = new Mobile(Mobile::state(Mobile::Back));
	mobiles[1] = new Mobile(Mobile::state(Mobile::Back | Mobile::Board));
	mobiles[2] = new Mobile(Mobile::state(Mobile::Back | Mobile::Board | Mobile::Chip));
	mobiles[3] = new Mobile(Mobile::state(Mobile::Back | Mobile::Board | Mobile::Chip | Mobile::Screen));
	mobiles[4] = new Mobile(Mobile::state(Mobile::Back | Mobile::Board | Mobile::Chip | Mobile::Screen | Mobile::Keys));
	mobiles[5] = new Mobile(Mobile::state(Mobile::Back | Mobile::Board | Mobile::Chip | Mobile::Screen | Mobile::Keys));

	robot1->attached = new Mobile(Mobile::Back);
	robot2->attached = new Mobile(Mobile::Board);
	robot3->attached = new Mobile(Mobile::Chip);
	robot4->attached = new Mobile(Mobile::Screen);
	robot5->attached = new Mobile(Mobile::Keys);

	robot2->attachFlipped = true;
	robot4->attachFlipped = true;
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
	glTranslatef(-28, 7, 5.5f);
	robot1->Render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14, 7, -5.5f);
	robot2->Render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 7, 5.5f);
	robot3->Render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(14, 7, -5.5f);
	robot4->Render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(28, 7, 5.5f);
	robot5->Render();
	glPopMatrix();

	for (int i = 0; i<mobilesOnBelt; i++)
	{
		glPushMatrix();
		glTranslatef(-28.0f+i*12+cyclepos*2.4f, 6.0f, 0);
		mobiles[i]->Render();
		glPopMatrix();
	}

}

void Factory::Process(float dt)
{
	conveyor->Process(dt);

	robot1->Process(dt);
	robot2->Process(dt);
	robot3->Process(dt);
	robot4->Process(dt);
	robot5->Process(dt);

	cyclepos += dt;

	Robot *botsList[] = {robot1, robot2, robot3, robot4, robot5};
	Mobile::state attachedTo[]  = {Mobile::Back, Mobile::Board, Mobile::Chip, Mobile::Screen, Mobile::Keys};

	const float timeOffsets = 0.8333333f;

	for (int i = 0; i<5; i++)
	{
		float adjustedCyclepos = fmod(cyclepos + timeOffsets*(6-i), cyclelen);
		float negated = i % 2 ? -1 : 1;
		if (adjustedCyclepos < 2.3)
		{
			if(i>0 && botsList[i]->attached)
			{
				Mobile *oldmobile = mobiles[i];
				mobiles[i] = mobiles[i]->Combine(dynamic_cast<Mobile*>(botsList[i]->attached));
				delete botsList[i]->attached;
				botsList[i]->attached = nullptr;
				delete oldmobile;
			}
			botsList[i]->setPos(0, 0,negated * 5.5f);
		}
		else if (adjustedCyclepos > 2.3 && adjustedCyclepos < 4.5)
		{
			if(!botsList[i]->attached)
			{
				botsList[i]->attached = new Mobile(attachedTo[i]);
			}
			botsList[i]->setPos(0, 0,negated * -5.5f);
			
		}
		else if (adjustedCyclepos > 4.5)
		{
			botsList[i]->setPos(0, -0.75,negated * -5.5f);
		}
	}

	if (cyclepos > cyclelen)
	{
		cyclepos -= cyclelen;	

		delete  mobiles[mobilesOnBelt-1];


		memcpy(&mobiles[1], mobiles, sizeof(void*)*(mobilesOnBelt-1));
		mobiles[0] = dynamic_cast<Mobile*>(robot1->attached);
		robot1->attached = nullptr;
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