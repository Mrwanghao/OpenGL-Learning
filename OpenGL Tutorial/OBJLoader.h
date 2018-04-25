#pragma once

#include <string>
#include "MTLLoader.h"

class OBJLoader
{
public:
	OBJLoader(const char *_mtlFileName, const char *_objFileName, int _vtNumber);
	~OBJLoader();

	int vCount;
	int faceCount;

	float **vData;
	float **vtData;
	float **vnData;

	int **fvData;
	int **fnData;
	int **ftData;

	std::string *mtlData;
	MTLLoader *mtlLoader;
private:
	const char *objFilePath;
	const char *mtlFilePath;
	int vtNumber;
	int vtCount;
	int vnCount;

	void readObjInfo();
	void readObjFile();

};

