#include "conveyor.h"
#include "common.h"

Conveyor::Conveyor()
{
}

Conveyor::~Conveyor()
{
}

void Conveyor::Process(double dt)
{
    float cyclesPerSec = 1.f;
    if (cyclesPerSec > 0)
    {
        cycleProgress = fmod(cycleProgress + cyclesPerSec * dt, 1);
    }
    else
    {
        cycleProgress = fmod((cycleProgress - 1) + dt * cyclesPerSec, 1) + 1;
    }
}

void Conveyor::Render()
{

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(-36, 10, -5);
    Frame();
    glPopMatrix();

    glColor3f(0.1, 0.1, 0.1);
	float spec_colour[3] = {.5f, .5f, .5f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 10); 

    //upper belt
    glPushMatrix();
    glTranslatef(-18 + 1.2 * cycleProgress, 5.7, 0);
    for (float i = 0; i <= 36; i += 1.2)
    {
        glPushMatrix();

        glScalef(1, 0.25, 4.4);
        glutSolidCube(1);
        glPopMatrix();
        glTranslatef(1.2, 0, 0);
    }
    glPopMatrix();

    //lower belt
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(-18 + 1.2 * cycleProgress, 4.3, 0);
    for (float i = 0; i <= 36; i += 1.2)
    {
        glPushMatrix();

        glScalef(1, 0.25, 4.4);
        glutSolidCube(1);
        glPopMatrix();
        glTranslatef(1.2, 0, 0);
    }
    glPopMatrix();
    
    glPushMatrix();

    for (int i = 0; i < 2; i++)
    {
    glPushMatrix();
    glTranslatef(-18, 5, 0);
    glRotatef(i*90 + 90*cycleProgress, 0,0,-1);
    glTranslatef(0,-0.7,0);
    glScalef(1, 0.25, 4.4);
    glutSolidCube(1);
    glPopMatrix();

    }
    glPopMatrix();
    for (int i = 0; i < 2; i++)
    {
    glPushMatrix();
    glTranslatef(18, 5, 0);
    glRotatef(i*90 + 90*cycleProgress + 180, 0,0,-1);
    glTranslatef(0,-0.7,0);
    glScalef(1, 0.25, 4.4);
    glutSolidCube(1);
    glPopMatrix();

    }
    
    glPopMatrix();
}

void Conveyor::Frame()
{
	float spec_colour[3] = {.4f, .4f, .4f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 3); 
    glColor3f(1.,1.,1.);
    GLUquadricObj *quadObj = gluNewQuadric();
    glPushMatrix();
    for (int i = 0; i < 10; i++)
    {
        gluCylinder(quadObj, 1, 1, 10, 20, 5);

        glPushMatrix();
        glRotatef(90, 1,0,0);
        gluCylinder(quadObj, 0.4, 0.4, 30, 20, 5);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, 10);
        glRotatef(90, 1,0,0);
        gluCylinder(quadObj, 0.4, 0.4, 30, 20, 5);
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
