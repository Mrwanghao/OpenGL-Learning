#include "ImageSet.h"


ImageSet::ImageSet()
	:
	_setID(0)
{
	_imageNames.clear();
	_nameAndIDMaps.clear();
}


ImageSet::~ImageSet()
{
	releaseTextureArray();
	_nameAndIDMaps.clear();
	for (unsigned int i = 0; i < _imageNames.size(); i++)
	{
		delete _images[i];
	}
	_images = nullptr;
	_imageNames.clear();

}


void ImageSet::addTexture(const char * name)
{
	_nameAndIDMaps[name] = _imageNames.size();
	_imageNames.push_back(name);
}

int ImageSet::findTexture(const char * name)
{
	std::map<std::string, int>::iterator iter = _nameAndIDMaps.find(name);
	if (iter != _nameAndIDMaps.end())
	{
		return iter->second;
	}
	return -1;
}

void ImageSet::initTextureArray(std::string dir)
{
	if (_imageNames.size() <= 0)
	{
		return;
	}
	_images = new BMPImage*[_imageNames.size()];

	glGenTextures(1, &_setID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _setID);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::string path = dir.append("/");
	std::string name("");
	for (unsigned int i = 0; i < _imageNames.size(); i++)
	{
		name = _imageNames[i];
		_images[i] = new BMPImage((path + name).c_str());
		if (i == 0)
		{
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, _images[i]->GetWidth(), _images[i]->GetHeight(), _imageNames.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, _images[i]->GetWidth(), _images[i]->GetHeight(), 1, GL_RGBA, GL_UNSIGNED_BYTE, _images[i]->GetData());
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void ImageSet::releaseTextureArray()
{
	if (_setID > 0)
	{
		glDeleteTextures(1, &_setID);
	}
}
