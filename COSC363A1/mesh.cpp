#include "common.h"
#include "mesh.h"
#include <fstream>
#include <sstream>

ObjMesh::ObjMesh(std::string fileName)
{
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
	if (optimized)
	{
		delete[] optimized;
	}
}

void ObjMesh::Render()
{
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_TRIANGLES);
	if (!optimized)
	{
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
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			//std::cout << optimized + i*12 << ":"<< i<<":"<< optimized[i * 12] << "\n";
			glNormal3fv(optimized + i * 12);
			glVertex3fv(optimized + i * 12 + 3);
			glVertex3fv(optimized + i * 12 + 6);
			glVertex3fv(optimized + i * 12 + 9);

		}
	}
	glEnd();
}

void ObjMesh::Process(float dt)
{

}

void ObjMesh::Optimize()
{
	if (!optimized)
	{
		n = faces.size();
		optimized = new float[n * 12];
		for (int i = 0; i < faces.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					optimized[i * 12 + j * 3 + k + 3] = verticies[faces[i][j] - 1][k];
				}
			}
			getNormal(optimized + i * 12 + 3, optimized + i * 12 + 6, optimized + i * 12 + 9, optimized + i * 12);
		}
	}
}