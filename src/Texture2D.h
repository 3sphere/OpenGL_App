#pragma once
#include <string>
#include <glad/glad.h>

class Texture2D
{
public:
	enum TextureFilter {NEAREST_NEIGHBOUR, BILINEAR, TRILINEAR};
	Texture2D(const std::string& filePath, TextureFilter filter = TRILINEAR);

	void bind(unsigned int textureUnit = 0);

private:
	unsigned int id;
	unsigned int width;
	unsigned int height;
};

