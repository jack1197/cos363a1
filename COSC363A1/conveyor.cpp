#include "conveyor.h"
#include "common.h"

Conveyor::Conveyor()
{
}

Conveyor::~Conveyor()
{
}

void Conveyor::Process(float dt)
{
	float cyclesPerSec = 2.f;
	if (cyclesPerSec > 0)
	{
		cycleProgress = float(fmod(cycleProgress + cyclesPerSec * dt, 1));
	}
	else
	{
		cycleProgress = float(fmod((cycleProgress - 1) + dt * cyclesPerSec, 1)) + 1;
	}
}

void Conveyor::Render()
{

	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(-36, 10, -5);
	Frame();
	glPopMatrix();

	glColor3f(0.1f, 0.1f, 0.1f);
	float spec_colour[3] = { .5f, .5f, .5f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 10);

	//upper belt
	glPushMatrix();
	glTranslatef(-18 + 1.2f * cycleProgress, 5.7f, 0);
	for (float i = 0; i <= 36; i += 1.2f)
	{
		glPushMatrix();

		glScalef(1, 0.25f, 4.4f);
		glutSolidCube(1);
		glPopMatrix();
		glTranslatef(1.2f, 0, 0);
	}
	glPopMatrix();

	//lower belt
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-18 + 1.2f * cycleProgress, 4.3f, 0);
	for (float i = 0; i <= 36; i += 1.2f)
	{
		glPushMatrix();

		glScalef(1, 0.25f, 4.4f);
		glutSolidCube(1);
		glPopMatrix();
		glTranslatef(1.2f, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();

	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(-18, 5, 0);
		glRotatef(i * 90 + 90 * cycleProgress, 0, 0, -1);
		glTranslatef(0, -0.7f, 0);
		glScalef(1, 0.25f, 4.4f);
		glutSolidCube(1);
		glPopMatrix();

	}
	glPopMatrix();
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(18, 5, 0);
		glRotatef(i * 90 + 90 * cycleProgress + 180, 0, 0, -1);
		glTranslatef(0, -0.7f, 0);
		glScalef(1, 0.25f, 4.4f);
		glutSolidCube(1);
		glPopMatrix();

	}

	glPopMatrix();
}

void Conveyor::Frame()
{
	float spec_colour[3] = { .4f, .4f, .4f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 3);
	glColor3f(.3f, .3f, .3f);
	GLUquadricObj *quadObj = gluNewQuadric();
	glPushMatrix();
	for (int i = 0; i < 10; i++)
	{
		gluCylinder(quadObj, 1, 1, 10, 20, 5);

		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadObj, 0.4f, 0.4f, 30, 20, 5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 10);
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadObj, 0.4f, 0.4f, 30, 20, 5);
		glPopMatrix();

		glTranslatef(8, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 0, 0);
	glScalef(76, 4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 0, 10);
	glScalef(76, 4, 1);
	glutSolidCube(1);
	glPopMatrix();
}
