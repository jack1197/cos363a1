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
	float height = 0.f;
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

	glRotatef(coreAngle, 0, 1, 0);

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
	gluCylinder(quadObj, sidelength / 2. - 0.7, sidelength / 2. - 0.7, 0.75, 40, 3);
	glPushMatrix();
	glRotatef(180, 0, 1,0 );
	gluDisk(quadObj, 0, sidelength / 2 - 0.7, 40, 3);
	glPopMatrix();
	glTranslatef(0, 0, 0.75);
	gluDisk(quadObj, 0, sidelength / 2 - 0.7, 40, 3);
	glPopMatrix();

	glTranslatef(0, sidelength / 2. - 0.7, 0);
	glPushMatrix();
	glTranslatef(0,0,-1);
	gluCylinder(quadObj, 0.75,0.75, 2, 30, 3);
	glPopMatrix();

	glRotatef(armAngle1, 0, 0, 1);
	//arm segment 1
	glPushMatrix();
	glTranslatef(0,armLength1/2,1);
	glScalef(2,armLength1+2,0.75);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,armLength1/2,-1);
	glScalef(2,armLength1+2,0.75);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0,armLength1,0);
	//Arm segment 2
	glRotatef(armAngle2, 0, 0,1);

	glPushMatrix();
	glTranslatef(0,0,-1);
	gluCylinder(quadObj, 0.75,0.75, 2, 30, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,(armLength2-1)/2,0);
	glScalef(2,armLength2+1,0.75);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0,armLength2,0);


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