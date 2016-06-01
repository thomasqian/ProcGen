#pragma once

#include "Skybox.h"

class Texture {
public:
	Texture(const char* filename);
	~Texture();

	GLuint textureID;

private:
	int width;
	int height;
};

