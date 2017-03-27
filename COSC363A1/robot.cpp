#include "robot.h"
#include "common.h"


Robot::Robot()
{
	setPos(7,-8,8);
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

	glColor3f(.8,.8,.4);
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

	glRotatef(180-coreAngle, 0, 1, 0);

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

void Robot::movementStep(double dt)
{
const float coreAnglePerSec = 80;
	const float arm1AnglePerSec = 45;
	const float arm2AnglePerSec = 80;

	float coreError = remainder(coreAngle - coreAngleTarget, 360);
	float arm1Error = armAngle1 - armAngle1Target;
	float arm2Error = armAngle2 - armAngle2Target;
	//std::cout<<"coreError: "<<coreError<<"\ttarget: "<<coreAngleTarget<<"\tcurrent: "<<coreAngle<<"\n";

	if (coreError > 0)
	{
		coreAngle -= coreAnglePerSec * dt;
		coreError = remainder(coreAngle - coreAngleTarget, 360);
		if (coreError < 0)
		coreAngle = coreAngleTarget;
	}
	else if (coreError < 0)
	{
		coreAngle += coreAnglePerSec * dt;
		coreError = remainder(coreAngle - coreAngleTarget, 360);
		if (coreError > 0)
		coreAngle = coreAngleTarget;
	}

	if (arm1Error > 0)
	{
		armAngle1 -= arm1AnglePerSec * dt;
		arm1Error = armAngle1 - armAngle1Target;
		if (arm1Error < 0)
		armAngle1 = armAngle1Target;
	}
	else if (arm1Error < 0)
	{
		armAngle1 += arm1AnglePerSec * dt;
		arm1Error = armAngle1 - armAngle1Target;
		if (arm1Error > 0)
		armAngle1 = armAngle1Target;
	}

	if (arm2Error > 0)
	{
		armAngle2 -= arm2AnglePerSec * dt;
		arm2Error = armAngle2 - armAngle2Target;
		if (arm2Error < 0)
		armAngle2 = armAngle2Target;
	}
	else if (arm2Error < 0)
	{
		armAngle2 += arm2AnglePerSec * dt;
		arm2Error = armAngle2 - armAngle2Target;
		if (arm2Error > 0)
		armAngle2 = armAngle2Target;
	}
}

void Robot::Process(double dt)
{
	time += dt;
	movementStep(dt);
}


void Robot::setAngles(float core, float arm1, float arm2)
{
	coreAngle = core;
	armAngle1 = arm1;
	armAngle2 = arm2;
}

void Robot::setPos(float x, float y , float z)
{
	float y_prime = y - axisHeight;
	float r = pow(pow(x, 2)+ pow( z, 2), 0.5);
	float d_squared = pow(y_prime, 2) + pow(r, 2);
	float d_angle = atan(y_prime/r);
	float theta_prime = acos((pow(armLength2, 2) - pow(armLength1, 2) - d_squared)/(-2*armLength1*pow(d_squared, 0.5)));
	float theta = PI/2 - d_angle - theta_prime;
	float phi = PI - acos((d_squared - pow(armLength1,2) - pow(armLength2, 2))/(-2*armLength1*armLength2));
	float gamma = atan(z/x) + (z<0 && y<0 ? PI : 0);

	coreAngleTarget = gamma / PI * 180.;
	armAngle1Target = theta / PI * 180.;
	armAngle2Target = phi / PI * 180.;
}