#include "Texture2D.h"
#include <iostream>
#include "stb_image.h"

Texture2D::Texture2D(const std::string& filePath, TextureFilter filter) :
	id(0),
	width(0),
	height(0)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering mode
	int minFilter, magFilter;
	switch (filter)
	{
		case NEAREST_NEIGHBOUR:
			minFilter = GL_NEAREST;
			magFilter = GL_NEAREST;
			break;
		case BILINEAR:
			minFilter = GL_LINEAR_MIPMAP_NEAREST;
			magFilter = GL_LINEAR;
			break;
		case TRILINEAR:
			minFilter = GL_LINEAR_MIPMAP_LINEAR;
			magFilter = GL_LINEAR;
			break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	int w, h, nrChannels, format = GL_RGB;
	unsigned char* image = stbi_load(filePath.c_str(), &w, &h, &nrChannels, 0);
	if (image)
	{
		if (nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		width = w;
		height = h;
	}
	else
	{
		std::cout << "Failed to load texture " << filePath << std::endl;
	}
	stbi_image_free(image);
}

void Texture2D::bind(unsigned int textureUnit)
{
	// OpenGL provides a maximum of 16 texture units
	unsigned int unit = textureUnit % 16;

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}
