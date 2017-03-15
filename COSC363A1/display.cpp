#include "common.h"
#include "display.h"
#include "camera.h"
/*
Render frame
*/
void render()
{
	//Setup frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cameraMatrix();

	float lightpos[4] = { -10.f, 50.f, 10.f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glScalef(100, 1, 100);
	glTranslatef(-0.5, 1, -0.5);
	concreteFloor(100, 3);
	//update screen
	glutSwapBuffers();
}

/*
concrete floor
*/
void concreteFloor(int subdivisions, int repetitions)
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (int i = 0; i < subdivisions; i++)
		for (int j = 0; j < subdivisions; j++)
		{
			float x1 = (float)i / (float)(subdivisions + 1);
			float x2 = (float)(i+1) / (float)(subdivisions + 1);
			float y1 = (float)j / (float)(subdivisions + 1);
			float y2 = (float)(j+1) / (float)(subdivisions + 1);
			glNormal3f(0, 1, 0);
			glTexCoord2f(x1*repetitions, y1*repetitions);
			glVertex3f(x1, 0, y1);
			glTexCoord2f(x1*repetitions, y2*repetitions);
			glVertex3f(x1, 0, y2);
			glTexCoord2f(x2*repetitions, y2*repetitions);
			glVertex3f(x2, 0, y2);
			glTexCoord2f(x2*repetitions, y1*repetitions);
			glVertex3f(x2, 0, y1);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}