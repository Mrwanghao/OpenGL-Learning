#include "BMPLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BMPLoader::BMPLoader()
{
	_header = (unsigned char *)malloc(54 * sizeof(unsigned char));
	memset(_header, 0, 54 * sizeof(unsigned char));
	_data = nullptr;
}

BMPLoader::~BMPLoader()
{
	if (_header) free(_header); _header = nullptr;
	if (_data) free(_data); _data = nullptr;
}

bool BMPLoader::loadBITMAP(const char * fileName)
{
	FILE *file = fopen(fileName, "rb");
	if (!file)
	{
		return false;
	}
	
	if (fread(_header, 1, 54, file) != 54)
	{
		return false;
	}

	if (_header[0] != 'B' || _header[1] != 'M')
	{
		return false;
	}

	_dataLocation = *(int *)&_header[0x0A];
	_imageSize = *(int *)&_header[0x22];
	_width = *(int *)&_header[0x12];
	_height = *(int *)&_header[0x16];
	_bit = *(unsigned short *)&_header[0x1C];

	_hasAlpha = (_bit == 32? true : false);

	int channelCount = _hasAlpha ? 4 : 3;

	if (_imageSize == 0)
	{
		_imageSize = _width * _height * channelCount;
	}

	if (_dataLocation == 0)
	{
		_dataLocation = 54;
	}

	_data = (unsigned char*)malloc(_imageSize * sizeof(unsigned char));

	memset(_data, 0, _imageSize * sizeof(unsigned char));
	fread(_data, 1, _imageSize, file);
	fclose(file);

	for (unsigned int i = 0; i < _imageSize; i += channelCount)
		SWAPCOLOR(_data[i], _data[i + 2]);
	
	if (!_hasAlpha)
	{
		_imageSize = _width * _height * 4;
		_bit = 32;
		_hasAlpha = true;
		unsigned char *temp = (unsigned char *)malloc(_imageSize * sizeof(unsigned char));
		
		for (unsigned int i = 0; i < _width * _height; i++)
		{
			temp[i * 4 + 0] = _data[i * 3 + 0];
			temp[i * 4 + 1] = _data[i * 3 + 1];
			temp[i * 4 + 2] = _data[i * 3 + 2];
			temp[i * 4 + 3] = 255;
		}

		free(_data);
		_data = NULL;
		_data = temp;
	}

	return true;
}
