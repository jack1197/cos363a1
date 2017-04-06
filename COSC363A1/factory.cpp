#include "factory.h"
#include "common.h"

Factory::Factory()
{
	floorTex = new Texture("TexturesCom_ConcreteBare0433_11_seamless_S.tga", "TGA");
	wallTex = new Texture("TexturesCom_BrickSmallBrown0270_1_seamless_S.tga", "TGA");
	conveyor = new Conveyor();
	conveyor2 = new Conveyor();
	conveyor2->cyclesPerSec = 1.f;
	float armLengths = 7;
	robot1 = new Robot(armLengths, armLengths);
	robot2 = new Robot(armLengths, armLengths);
	robot3 = new Robot(armLengths, armLengths);
	robot4 = new Robot(armLengths, armLengths);
	robot5 = new Robot(armLengths, armLengths);

	mobiles[0] = new Mobile(Mobile::state(Mobile::Back));
	mobiles[1] = new Mobile(Mobile::state(Mobile::Back));
	mobiles[2] = new Mobile(Mobile::state(Mobile::BackAndBoard));
	mobiles[3] = new Mobile(Mobile::state(Mobile::BackAssembly));
	mobiles[4] = new Mobile(Mobile::state(Mobile::BackAndKeys));
	mobiles[5] = new Mobile(Mobile::state(Mobile::Full));

	robot1->attached = new Mobile(Mobile::Back);
	robot2->attached = new Mobile(Mobile::BoardChipScreen);
	robot3->attached = new Mobile(Mobile::Antenna);
	robot4->attached = new Mobile(Mobile::Keys);
	robot5->attached = new Mobile(Mobile::Front);

	robot2->attachFlipped = true;
	robot4->attachFlipped = true;

	Robot *botsList[] = {robot1, robot2, robot3, robot4, robot5};
	for ( int i = 0; i<5; i++)
	{
		botsList[i]->attachedOffset[1] = robotOffsets[i];
	}
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
	glTranslatef(25.5f, 0, 10);
	conveyor->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, 0, 10);
	conveyor->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.5, 0, -12);
	glRotatef(-90, 0 ,1,0);
	conveyor2->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,10);
	Robot *botsList[] = {robot1, robot2, robot3, robot4, robot5};
	for(int i =0; i<5; i++)
	{
		float negated = i % 2 ? -1 : 1;
		glPushMatrix();
		glTranslatef(-28+14*i, 6.00f-robotOffsets[i], negated * 5.5f);
		botsList[i]->Render();
		glPopMatrix();
		if(i!=1)
		{
		glPushMatrix();
		glColor3f(165./255., 136./255., 85./255.);
		float spec_colour[3] = {165./255./4., 136./255./4., 85./255./4.};
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
		glMaterialf(GL_FRONT, GL_SHININESS, 2);
		glTranslatef(-28+14*i, 2.5f, negated * 11.0f);
		glutSolidCube(5);
		glPopMatrix();
		}
	}

	for (int i = 0; i<mobilesOnBelt; i++)
	{
		glPushMatrix();
		glTranslatef(-28.0f+i*12+cyclepos*2.4f, 6.0f, 0);
		mobiles[i]->Render();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(-8.5, 0, -12);
	glRotatef(-90, 0, 1, 0);
	for (int i = 0; i<mobilesOnBelt2; i++)
	{
		glPushMatrix();
		glTranslatef(-28.0f+i*6+cyclepos*1.2f, 6.0f, 0);
		mobiles[i]->Render();
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

}

void Factory::Process(float dt)
{
	conveyor->Process(dt);
	conveyor2->Process(dt);

	robot1->Process(dt);
	robot2->Process(dt);
	robot3->Process(dt);
	robot4->Process(dt);
	robot5->Process(dt);

	cyclepos += dt;

	Robot *botsList[] = {robot1, robot2, robot3, robot4, robot5};
	Mobile::state attachedTo[]  = {Mobile::Back, Mobile::BoardChipScreen, Mobile::Antenna, Mobile::Keys, Mobile::Front};

	const float timeOffsets = 0.8333333f;

	for (int i = 0; i<5; i++)
	{
		float adjustedCyclepos = fmod(cyclepos + timeOffsets*(6-i), cyclelen);
		float negated = i % 2 ? -1 : 1;
		if (adjustedCyclepos < 1.8)
		{
			if(i>0 && botsList[i]->attached)
			{
				Mobile *oldmobile = mobiles[i];
				mobiles[i] = mobiles[i]->Combine(dynamic_cast<Mobile*>(botsList[i]->attached));
				delete botsList[i]->attached;
				botsList[i]->attached = nullptr;
				delete oldmobile;
			}
			if(i!=1)
			botsList[i]->setPos(0, 1,negated * 5.5f);
			else
			botsList[i]->setPos(5.5f, 1,0);
		}
		else if (adjustedCyclepos > 1.8 && adjustedCyclepos < 2.3)
		{
			if(i!=1)
			botsList[i]->setPos(0, -3,negated * 5.5f);
			else
			botsList[i]->setPos(5.5f, 0,0);
		}
		else if (adjustedCyclepos > 2.3 && adjustedCyclepos < 2.8)
		{
			if(!botsList[i]->attached)
			{
				botsList[i]->attached = new Mobile(attachedTo[i]);

			}
			if(i!=1)
			botsList[i]->setPos(0, 1,negated * 5.5f);
			else
			botsList[i]->setPos(5.5f, 1,0);
		}
		else if (adjustedCyclepos > 2.8 && adjustedCyclepos < 4.85)
		{
			botsList[i]->setPos(0, 1,negated * -5.5f);
			
		}
		else if (adjustedCyclepos > 4.85f)		
			{
			botsList[i]->setPos(0, 0,negated * -5.5f);
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