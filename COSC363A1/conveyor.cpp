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

}

void Conveyor::Render()
{
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glTranslatef(-36,10, -5);
    Frame();
    glPopMatrix();
    glColor3f(0.2,0.2,0.2);
    
    glPushMatrix();
    glTranslatef(-18,5.7,0);
    for(float i = 0; i<=36; i+=1.2)
    {
    glPushMatrix();

    glScalef(1, 0.25, 4.4);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(1.2,0,0);
    }
    glPopMatrix();
}

void Conveyor::Frame()
{
    GLUquadricObj *quadObj = gluNewQuadric();
    glPushMatrix();
    for(int i = 0; i<10; i++)
    {
        gluCylinder(quadObj, 1, 1, 10, 20, 5);
        glTranslatef(8,0,0);

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
