#include "BMPImage.h"



BMPImage::BMPImage(const char *fileName)
{
	
}


BMPImage::~BMPImage()
{
	if (mBMPLoader) delete mBMPLoader; mBMPLoader = nullptr;
}

unsigned char * BMPImage::GetData()
{
	return mBMPLoader->GetData();
}

void BMPImage::LoadHeightMap(const char *fileName)
{
	mBMPLoader->loadBITMAP(fileName);
}
