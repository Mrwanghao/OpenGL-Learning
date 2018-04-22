#pragma once




#define SWAPCOLOR(a, b){ \
						(a) ^= (b); \
						(b) ^= (a); \
						(a) ^= (b);\
}


class BMPLoader
{
public:
	BMPLoader();
	~BMPLoader();

public:
	bool loadBITMAP(const char *fileName);

public:
	unsigned char *_data;

	inline unsigned int GetWidth() const { return _width; }
	inline unsigned int GetHeight() const { return _height; }
	inline unsigned char* GetData() const { return _data; }

private:
	unsigned char *_header;
	unsigned int _dataLocation;
	unsigned int _width, _height;
	unsigned int _imageSize;
	unsigned short _bit;
	bool _hasAlpha;

};
