#pragma once

#include "BMPLoader.h"

class BMPImage
{
public:
	BMPImage();
	~BMPImage();

public:
	unsigned char* GetData();
	inline unsigned int GetWidth() { return mBMPLoader->GetWidth(); }
	inline unsigned int GetHeight() { return mBMPLoader->GetHeight(); }
	void LoadHeightMap(const char * fileName);
private:
	BMPLoader * mBMPLoader;
};

