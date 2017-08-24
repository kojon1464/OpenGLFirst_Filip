#pragma once

#include "stb_image.h"
#include <glad\glad.h>
#include <iostream>

class Texture
{
public:
	Texture(const char* path, GLenum format);

	void activateAndBindTexture(GLenum texture);

	virtual ~Texture();
private:
	unsigned int m_texture;
};

