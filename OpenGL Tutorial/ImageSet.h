#pragma once

#include "BMPImage.h"
#include <map>
#include <vector>
#include <glad/glad.h>
#include <string>

class ImageSet
{
private:
	BMPImage * *_images;
	std::map<std::string, int> _nameAndIDMaps;

	void releaseTextureArray();

public:
	GLuint _setID;
	std::vector<std::string> _imageNames;

public:
	ImageSet();
	~ImageSet();

	void addTexture(const char *name);
	int findTexture(const char *name);
	void initTextureArray(std::string dir);
};

