#include "part_box.h"


int PartBox::objCount = 0;
Texture *PartBox::cardboardTex = nullptr;

PartBox::PartBox()
{
	objCount++;
	if (objCount == 1)
	{
		cardboardTex = new Texture("TexturesCom_CardboardPlain0008_1_seamless_S.tga");
	}
}


PartBox::~PartBox()
{
	objCount--;
	if (objCount == 0)
	{
		delete cardboardTex;
	}
}

void PartBox::Render()
{
	glColor3f(2.0f, 2.0f, 2.0f);
	float spec_colour[3] = { 0.8f,0.8f,0.8f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 5);
	glPushMatrix();
	float flatSurfaceVerticies[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	glEnable(GL_TEXTURE_2D);
	cardboardTex->bind();
	for (int j = 0; j < 4; j++)
	{
		glPushMatrix();
		glRotatef(90 * j, 0, 1, 0);
		glTranslatef(-0.5, 0, -0.5);
		glRotatef(-90, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 4; i++)
		{
			setNormal(flatSurfaceVerticies + i * 9, flatSurfaceVerticies + i * 9 + 3, flatSurfaceVerticies + i * 9 + 6);
			glTexCoord2f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[2 + i * 9]);
			glVertex3f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[1 + i * 9], flatSurfaceVerticies[2 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[5 + i * 9]);
			glVertex3f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[4 + i * 9], flatSurfaceVerticies[5 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[8 + i * 9]);
			glVertex3f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[7 + i * 9], flatSurfaceVerticies[8 + i * 9]);
		}
		glEnd();
		glPopMatrix();
	}
	for (int j = 0; j < 4; j++)
	{
		glPushMatrix();
		glRotatef(90 * j, 0, 1, 0);
		glTranslatef(-0.5, 1.0f, -0.5);
		glRotatef(-150, 1, 0, 0);
		glScalef(1,1,0.5f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 4; i++)
		{
			setNormal(flatSurfaceVerticies + i * 9, flatSurfaceVerticies + i * 9 + 3, flatSurfaceVerticies + i * 9 + 6);
			glTexCoord2f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[2 + i * 9]/2);
			glVertex3f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[1 + i * 9], flatSurfaceVerticies[2 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[5 + i * 9]/2);
			glVertex3f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[4 + i * 9], flatSurfaceVerticies[5 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[8 + i * 9]/2);
			glVertex3f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[7 + i * 9], flatSurfaceVerticies[8 + i * 9]);
		}
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	//blackness
	float spec_colour2[3] = { 0.0f,0.0f,0.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour2);
	for (int j = 0; j < 9; j++)
	{
		glPushMatrix();
		glTranslatef(-0.5, 0.7 + j*0.03333, -0.5);
		glScalef(0.999, 1, 0.999);
		glBegin(GL_TRIANGLES);
		glColor4f(0.f, 0.f, 0.f, 1.0f - 0.1f*j);
		for (int i = 0; i < 4; i++)
		{
			setNormal(flatSurfaceVerticies + i * 9, flatSurfaceVerticies + i * 9 + 3, flatSurfaceVerticies + i * 9 + 6);
			glTexCoord2f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[2 + i * 9]);
			glVertex3f(flatSurfaceVerticies[0 + i * 9], flatSurfaceVerticies[1 + i * 9], flatSurfaceVerticies[2 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[5 + i * 9]);
			glVertex3f(flatSurfaceVerticies[3 + i * 9], flatSurfaceVerticies[4 + i * 9], flatSurfaceVerticies[5 + i * 9]);
			glTexCoord2f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[8 + i * 9]);
			glVertex3f(flatSurfaceVerticies[6 + i * 9], flatSurfaceVerticies[7 + i * 9], flatSurfaceVerticies[8 + i * 9]);
		}
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

void PartBox::Process(float dt)
{

}