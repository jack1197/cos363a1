#include "common.h"
#include "loadTGA.h"
#include "loadBMP.h"
#include <string>
#include "texture.h"

Texture::Texture(std::string fileName, std::string type)
{
	glGenTextures(1, &txId);
	glBindTexture(GL_TEXTURE_2D, txId);
#ifndef _WIN32
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#else
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif
	if (type == "TGA")
	{
		loadTGA(fileName.c_str());
	}
	else if (type == "BMP")
	{
		loadBMP(fileName.c_str());
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Texture::~Texture()
{
	glDeleteTextures(1, &txId);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, txId);
}