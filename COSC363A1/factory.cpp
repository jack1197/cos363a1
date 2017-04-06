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
	robot6 = new Robot(armLengths, armLengths);

	robotb1 = new Robot(armLengths, armLengths);
	robotb2 = new Robot(armLengths, armLengths);
	robotb3 = new Robot(armLengths, armLengths);

	mobiles[0] = new Mobile(Mobile::state(Mobile::Back));
	mobiles[1] = new Mobile(Mobile::state(Mobile::Back));
	mobiles[2] = new Mobile(Mobile::state(Mobile::BackAndBoard));
	mobiles[3] = new Mobile(Mobile::state(Mobile::BackAssembly));
	mobiles[4] = new Mobile(Mobile::state(Mobile::BackAndKeys));
	mobiles[5] = new Mobile(Mobile::state(Mobile::Full));

	mobiles2[0] = new Mobile(Mobile::Board);
	mobiles2[1] = new Mobile(Mobile::BoardChip);
	for (int i = 2; i < mobilesOnBelt2; i++)
	{
		mobiles2[i] = new Mobile(Mobile::BoardChipScreen);
	}

	robot1->attached = new Mobile(Mobile::Back);
	robot2->attached = new Mobile(Mobile::BoardChipScreen);
	robot3->attached = new Mobile(Mobile::Antenna);
	robot4->attached = new Mobile(Mobile::Keys);
	robot5->attached = new Mobile(Mobile::Front);
	robot6->attached = new Mobile(Mobile::Full);

	robotb1->attached = new Mobile(Mobile::Board);
	robotb2->attached = new Mobile(Mobile::Chip);
	robotb3->attached = new Mobile(Mobile::Screen);

	robot2->attachFlipped = true;
	robot4->attachFlipped = true;
	robot6->attachFlipped = true;

	robotb2->attachFlipped = true;

	Robot *botsList[] = { robot1, robot2, robot3, robot4, robot5, robot6 };
	for (int i = 0; i < 6; i++)
	{
		botsList[i]->attachedOffset[1] = robotOffsets[i];
	}

	Robot *botsList2[] = { robotb1, robotb2, robotb3 };
	for (int i = 0; i < 3; i++)
	{
		botsList2[i]->attachedOffset[1] = robotOffsets2[i];
	}
}

Factory::~Factory()
{
	delete floorTex;
	delete wallTex;
	delete conveyor;
	delete robot1;
	delete robot2;
	delete robot3;
	delete robot4;
	delete robot5;
	delete conveyor2;

	for (int i = 0; i < mobilesOnBelt; i++)
	{
		delete mobiles[i];
	}
}

void Factory::Render()
{
	//floor
	glPushMatrix();
	glScalef(100, 1, 100);
	glTranslatef(-0.5f, 0.f, -0.5f);
	concreteFloor(100, 3);
	glPopMatrix();

	//walls
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

	//main belt 1
	glPushMatrix();
	glTranslatef(27.5f, 0, 10);
	conveyor->Render();
	glPopMatrix();

	//main belt 2
	glPushMatrix();
	glTranslatef(-11, 0, 10);
	conveyor->Render();
	glPopMatrix();

	//aux belt 1
	glPushMatrix();
	glTranslatef(-19.5, 0, -12);
	glRotatef(-90, 0, 1, 0);
	conveyor2->Render();
	glPopMatrix();

	//main robots

	glPushMatrix();
	glTranslatef(0, 0, 10);
	Robot *botsList[] = { robot1, robot2, robot3, robot4, robot5, robot6 };
	for (int i = 0; i < 6; i++)
	{
		float negated = i % 2 ? -1 : 1;
		glPushMatrix();
		glTranslatef(-28 + 14 * i, 6.00f - robotOffsets[i], negated * 5.5f);
		botsList[i]->Render();
		glPopMatrix();
		if (i != 1)
		{
			glPushMatrix();
			glColor3f(165. / 255., 136. / 255., 85. / 255.);
			float spec_colour[3] = { 165. / 255. / 4., 136. / 255. / 4., 85. / 255. / 4. };
			glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
			glMaterialf(GL_FRONT, GL_SHININESS, 2);
			glTranslatef(-28 + 14 * i, 2.5f, negated * 11.0f);
			glScalef(2, 1, 1);
			glutSolidCube(5);
			glPopMatrix();
		}
	}
	//main mobiles

	for (int i = 0; i < mobilesOnBelt; i++)
	{
		if (i != 5 || cyclepos < 4.1666666f)
		{
			glPushMatrix();
			glTranslatef(-28.0f + i * 12 + cyclepos*2.4f, 6.0f, 0);
			mobiles[i]->Render();
			glPopMatrix();
		}
	}
	glPopMatrix();

	//aux mobiles
	glPushMatrix();
	glTranslatef(-19.5, 0, 3);
	glRotatef(-90, 0, 1, 0);
	for (int i = 0; i < mobilesOnBelt2; i++)
	{
		glPushMatrix();
		glTranslatef(-28.5f + i * 6 + fmod((cyclepos + 1.85f), cyclelen)*1.2f, 6.0f, 0);
		mobiles2[i]->Render();
		glPopMatrix();
	}
	glPopMatrix();

	//aux robots
	glPushMatrix();
	glTranslatef(-19.5, 0, 2.5);
	glRotatef(-90, 0, 1, 0);
	Robot *botsList2[] = { robotb1, robotb2, robotb3 };
	for (int i = 0; i < 3; i++)
	{
		float negated = i % 2 ? -1 : 1;
		glPushMatrix();
		glTranslatef(-28 + 7 * i, 6.00f - robotOffsets2[i], negated * 5.5f);
		botsList2[i]->Render();
		glPopMatrix();
		glPushMatrix();
		glColor3f(165. / 255., 136. / 255., 85. / 255.);
		float spec_colour[3] = { 165. / 255. / 4., 136. / 255. / 4., 85. / 255. / 4. };
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
		glMaterialf(GL_FRONT, GL_SHININESS, 2);
		glTranslatef(-28 + 7 * i, 2.5f, negated * 11.0f);
		glScalef(1, 1, 1);
		glutSolidCube(5);
		glPopMatrix();
	}
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
	robot6->Process(dt);

	robotb1->Process(dt);
	robotb2->Process(dt);
	robotb3->Process(dt);


	cyclepos += dt;

	Robot *botsList[] = { robot1, robot2, robot3, robot4, robot5 };
	int colorIndexs[] = { 0, 1, 2, 3, 4 };
	int colorSettings[] = { 0, 0, 5, 6, 1 };
	Mobile::state attachedTo[] = { Mobile::Back, Mobile::BoardChipScreen, Mobile::Antenna, Mobile::Keys, Mobile::Front };

	const float timeOffsets = 0.8333333f;

	for (int i = 0; i < 5; i++)
	{
		float adjustedCyclepos = fmod(cyclepos + timeOffsets*(6 - i) + (i == 0 ? 0.1f : 0.f), cyclelen);
		float negated = i % 2 ? -1 : 1;
		if (adjustedCyclepos < 1.8)
		{
			if (botsList[i]->attached && i != 0) //i>0 && 
			{
				Mobile *oldmobile = mobiles[i];
				mobiles[i] = mobiles[i]->Combine(dynamic_cast<Mobile*>(botsList[i]->attached));
				delete botsList[i]->attached;
				botsList[i]->attached = nullptr;
				delete oldmobile;
			}
			if (i != 1)
				botsList[i]->setPos(0, 1, negated * 5.5f);
			else
				botsList[i]->setPos(-5.5f, 1, 0);
		}
		else if (adjustedCyclepos > 1.8 && adjustedCyclepos < 2.3)
		{
			if (i != 1)
				botsList[i]->setPos(0, -3, negated * 5.5f);
			else
				botsList[i]->setPos(-5.5f, 0, 0);
		}
		else if (adjustedCyclepos > 2.3 && adjustedCyclepos < 2.8)
		{
			if (!botsList[i]->attached && i != 1)
			{
				botsList[i]->attached = new Mobile(attachedTo[i]);
				for (int j = 0; j < 4; j++)
				{
					float lower = colorMins[colorIndexs[i]][j];
					float upper = colorMaxs[colorIndexs[i]][j];
					dynamic_cast<Mobile*>(botsList[i]->attached)->colors[colorSettings[i]][j] = (upper - lower) * randomDist(generator) + lower;
				}
			}
			if (i != 1)
				botsList[i]->setPos(0, 1, negated * 5.5f);
			else
				botsList[i]->setPos(-5.5f, 1, 0);
		}
		else if (adjustedCyclepos > 2.8 && adjustedCyclepos < 4.85)
		{
			botsList[i]->setPos(0, 1, negated * -5.5f);

		}
		else if (adjustedCyclepos > 4.85f)
		{
			botsList[i]->setPos(0, 0, negated * -5.5f);
		}
	}

	Robot *botsList2[] = { robotb1, robotb2, robotb3 };
	Mobile::state attachedTo2[] = { Mobile::Board, Mobile::Chip, Mobile::Screen };
	int colorIndexs2[] = { 5, 6, 7 };
	int colorSettings2[] = { 2, 3, 4 };

	for (int i = 0; i < 3; i++)
	{
		float adjustedCyclepos = fmod(cyclepos + timeOffsets*(6 - i) + 1.85f, cyclelen);
		float negated = i % 2 ? -1 : 1;
		if (adjustedCyclepos < 1.8)
		{
			if (botsList2[i]->attached && i != 0)
			{
				Mobile *oldmobile = mobiles2[i];
				mobiles2[i] = mobiles2[i]->Combine(dynamic_cast<Mobile*>(botsList2[i]->attached));
				delete botsList2[i]->attached;
				botsList2[i]->attached = nullptr;
				delete oldmobile;
			}
			botsList2[i]->setPos(0, 1, negated * 5.5f);
		}
		else if (adjustedCyclepos > 1.8 && adjustedCyclepos < 2.3)
		{
			botsList2[i]->setPos(0, -3, negated * 5.5f);
		}
		else if (adjustedCyclepos > 2.3 && adjustedCyclepos < 2.8)
		{
			if (!botsList2[i]->attached)
			{
				botsList2[i]->attached = new Mobile(attachedTo2[i]);
				for (int j = 0; j < 4; j++)
				{
					float lower = colorMins[colorIndexs2[i]][j];
					float upper = colorMaxs[colorIndexs2[i]][j];
					dynamic_cast<Mobile*>(botsList2[i]->attached)->colors[colorSettings2[i]][j] = (upper - lower) * randomDist(generator) + lower;
				}

			}
			botsList2[i]->setPos(0, 1, negated * 5.5f);
		}
		else if (adjustedCyclepos > 2.8 && adjustedCyclepos < 4.85)
		{
			botsList2[i]->setPos(0, 1, negated * -5.5f);

		}
		else if (adjustedCyclepos > 4.85f)
		{
			botsList2[i]->setPos(0, 0, negated * -5.5f);
		}
	}

	if (cyclepos + 1.85f > 5.0f)
	{
		if (!robot2->attached)
		{
			robot2->attached = mobiles2[mobilesOnBelt2 - 1];
			memcpy(&mobiles2[1], mobiles2, sizeof(void*)*(mobilesOnBelt2 - 1));
			if (robotb1->attached)
			{
				mobiles2[0] = dynamic_cast<Mobile*>(robotb1->attached);
				robotb1->attached = nullptr;
			}
			else
			{
				mobiles2[0] = new Mobile(Mobile::state(0));
			}
		}
	}

	if (cyclepos > 4.166666f)
	{
		robot6->attached = mobiles[mobilesOnBelt - 1];
	}


	{
		float adjustedCyclepos = fmod(cyclepos + 0.833333f, cyclelen);
		if (adjustedCyclepos < 1.8)
		{
			robot6->setPos(0, 1, -5.5f);
		}
		else if (adjustedCyclepos < 2.5)
		{
			robot6->setPos(0, -3, -5.5f);
		}
		else if (adjustedCyclepos < 3.0)
		{
			if (robot6->attached)
			{
				delete robot6->attached;
				robot6->attached = nullptr;
			}
			robot6->setPos(0, 1, -5.5f);
		}
		else if (adjustedCyclepos < 4.85f)
		{
			robot6->setPos(0, 1, 5.5f);
		}
		else
		{
			robot6->setPos(0, 0, 5.5f);
		}
	}

	if (cyclepos > cyclelen)
	{
		cyclepos = fmod(cyclepos, cyclelen);

		memcpy(&mobiles[1], mobiles, sizeof(void*)*(mobilesOnBelt - 1));
		if (robot1->attached)
		{
			mobiles[0] = dynamic_cast<Mobile*>(robot1->attached);
			robot1->attached = nullptr;
		}
		else
		{
			mobiles[0] = new Mobile(Mobile::state(0));
		}
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