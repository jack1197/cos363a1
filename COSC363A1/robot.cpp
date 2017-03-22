#include "robot.h"
#include "common.h"


Robot::Robot()
{
}


Robot::~Robot()
{
}


void Robot::Render()
{
	float height = 7.f;
	float base = 40.0f;
	float sidelength = 5.0f;
	float baseCylHeight = 1.f;
	GLUquadric *quadObj = gluNewQuadric();

	float spec_colour[3] = { .8f, .8f, .4f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2);

	glPushMatrix();
	glTranslatef(0, height, 0);

	//base
	glPushMatrix();
	glTranslatef(0,-base/2.f,0);
	glScalef(sidelength, base, sidelength);
	glutSolidCube(1);
	glPopMatrix();

	//core axis
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadObj, sidelength / 2. - 0.5, sidelength / 2. - 0.5, baseCylHeight, 30, 3);
	glTranslatef(0, 0, baseCylHeight);
	gluDisk(quadObj, 0, sidelength / 2 - 0.5, 30, 3);
	glPopMatrix();

	glTranslatef(0, baseCylHeight, 0);
	glPushMatrix();
	glPushMatrix();
	glScalef(sidelength / 2. - 0.7, sidelength / 2. - 0.7, 0.75/2);
	glutSolidCube(2);
	glPopMatrix();
	glTranslatef(0, sidelength / 2. - 0.7, -0.75/2);
	gluCylinder(quadObj, sidelength / 2. - 0.7, sidelength / 2. - 0.7, 0.75, 30, 3);
	glPushMatrix();
	glRotatef(180, 0, 1,0 );
	gluDisk(quadObj, 0, sidelength / 2 - 0.7, 30, 3);
	glPopMatrix();
	glTranslatef(0, 0, 0.75);
	gluDisk(quadObj, 0, sidelength / 2 - 0.7, 30, 3);
	glPopMatrix();

	glPopMatrix();
}

void Robot::Process(double dt)
{

}


void Robot::setAngles(float core, float arm1, float arm2)
{
	coreAngle = core;
	armAngle1 = arm1;
	armAngle2 = arm2;
}