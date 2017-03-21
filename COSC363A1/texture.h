#pragma once
#include <string>

class Texture {
	unsigned int txId;
public:
	Texture(std::string fileName, std::string type = "TGA");
	~Texture();
	void bind();
};