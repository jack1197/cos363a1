#include "common.h"
#include "mesh.h"
#include <fstream>
#include <sstream>

ObjMesh::ObjMesh(std::string fileName, float color[4])
{
	for (int i = 0; i < 4; i++)
		this->color[i] = color[i];
	std::ifstream file;
	file.open(fileName);
	std::string line;
	if (!file.is_open())
	{
		std::cout << "could not open mesh: " << fileName << "\n";
		return;
	}
	int n = 0;
	while (std::getline(file, line))
	{
		std::istringstream strstream(line);
		char firstChar;
		strstream >> firstChar;
		if (line.at(0) == 'v')
		{
			float *vertex = new float[3];
			strstream >> vertex[0];
			strstream >> vertex[1];
			strstream >> vertex[2];
			verticies.push_back(vertex);
			//std::cout<<n++<<"\n";
		}
		else if (line.at(0) == 'f')
		{
			int *face = new int[3];
			strstream >> face[0];
			strstream >> face[1];
			strstream >> face[2];
			faces.push_back(face);
		}
	}
}

void setNormal(float v1[3], float v2[3], float v3[3])
{
	float n[3];
	n[0] = v1[1] * (v2[2] - v3[2]) + v2[1] * (v3[2] - v1[2]) + v3[1] * (v1[2] - v2[2]);
	n[1] = v1[2] * (v2[0] - v3[0]) + v2[2] * (v3[0] - v1[0]) + v3[2] * (v1[0] - v2[0]);
	n[2] = v1[0] * (v2[1] - v3[1]) + v2[0] * (v3[1] - v1[1]) + v3[0] * (v1[1] - v2[1]);
	glNormal3f(n[0], n[1], n[2]);
}

ObjMesh::~ObjMesh()
{
	for (auto whatever : verticies)
	{
		delete[] whatever;
	}
	for (auto whatever : faces)
	{
		delete[] whatever;
	}
}

void ObjMesh::Render()
{
	float spec_colour[3] = { .8f, .8f, .8f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec_colour);
	glMaterialf(GL_FRONT, GL_SHININESS, 2);
	glColor4fv(color);
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_TRIANGLES);
	for (int *face : faces)
	{
		setNormal(verticies[face[0] - 1], verticies[face[1] - 1], verticies[face[2] - 1]);
		for (int i = 0; i < 3; i++)
		{
			int vertex = face[i] - 1;
			//std::cout<<"making vertex "<<vertex<<"\n";
			glVertex3f(verticies[vertex][0], verticies[vertex][1], verticies[vertex][2]);
		}
	}
	glEnd();
}

void ObjMesh::Process(float dt)
{

}