#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>


OBJLoader::OBJLoader(const char *_mtlFileName, const char *_objFileName, int _vtNumber)
	:
	mtlFilePath(_mtlFileName),
	objFilePath(_objFileName),
	vtNumber(_vtNumber),
	vData(0),
	vnData(0),
	vtData(0),
	faceCount(0)
{
	readObjInfo();
	readObjInfo();
	mtlLoader = new MTLLoader(mtlFilePath);
}


OBJLoader::~OBJLoader()
{
	for (int i = 0; i < vCount; i++)
	{
		delete[] vData[i];
	}

	for (int i = 0; i < vnCount; i++)
	{
		delete[] vnData[i];
	}

	for (int i = 0; i < vtCount; i++)
	{
		delete[] vtData[i];
	}

	for (int i = 0; i < faceCount; i++)
	{
		delete[] fvData[i];
		delete[] ftData[i];
		delete[] fnData[i];
	}

	delete[] vData;
	delete[] vnData;
	delete[] vtData;
	delete[] fvData;
	delete[] fnData;
	delete[] ftData;
	delete[] mtlData;
	
	delete mtlLoader;
	mtlData = nullptr;
}

void OBJLoader::readObjInfo()
{
	std::ifstream ifs(objFilePath);
	std::string content;

	while (getline(ifs, content))
	{
		if (content[0] == 'v') 
		{
			if (content[1] == 'n')
			{
				vnCount++;
			}
			else if (content[1] == 't')
			{
				vtCount++;
			}
			else
			{
				vCount++;
			}
		}

		if (content[0] == 'f')
		{
			faceCount++;
		}
	}

	ifs.close();
}

void OBJLoader::readObjFile()
{
	vData = new float*[vCount];
	for (int i = 0; i < vCount; i++)
	{
		vData[i] = new float[3];
	}

	vnData = new float*[vnCount];
	for (int i = 0; i < vnCount; i++)
	{
		vnData[i] = new float[3];
	}

	vtData = new float*[vtCount];
	for (int i = 0; i < vtCount; i++)
	{
		vtData[i] = new float[vtNumber];
	}

	fvData = new int*[faceCount];
	ftData = new int*[faceCount];
	fnData = new int*[faceCount];
	for (int i = 0; i < faceCount; i++)
	{
		fvData[i] = new int[3];
		ftData[i] = new int[3];
		fnData[i] = new int[3];
	}
	mtlData = new std::string[faceCount];

	std::ifstream ifs(objFilePath);
	std::string content;
	int ii = 0, tt = 0, jj = 0, kk = 0;

	std::string s1;
	float f2, f3, f4;
	std::string mtl("");

	while (getline(ifs, content))
	{
		if (content[0] == 'v')
		{
			if (content[1] == 'n')
			{
				std::istringstream iss(content);
				iss >> s1 >> f2 >> f3 >> f4;
				vnData[ii][0] = f2;
				vnData[ii][1] = f3;
				vnData[ii][2] = f4;
				ii++;
			}
			else if (content[1] == 't')
			{
				std::stringstream iss(content);
				if (vtNumber == 3)
				{
					iss >> s1 >> f2 >> f3 >> f4;
					vtData[tt][0] = f2;
					vtData[tt][1] = f3;
					vtData[tt][2] = f4;
				}
				else
				{
					iss >> s1 >> f2 >> f3;
					vtData[tt][0] = f2;
					vtData[tt][1] = f3;
				}
			}
			else
			{
				std::istringstream iss(content);
				iss >> s1 >> f2 >> f3 >> f4;
				vData[jj][0] = f2;
				vData[jj][1] = f3;
				vData[jj][2] = f4;
				jj++;
			}
		}
		else if (content[0] = 'f')
		{
			std::istringstream iss(content);
			float a;
			iss >> s1;
			int i, k;

			for (int i = 0; i < 3; i++)
			{
				iss >> s1;

				a = 0;
				for (k = 0; s1[k] != '/'; k++)
				{
					a = a * 10 + s1[k] - 48;
				}
				fvData[kk][i] = a;

				a = 0;
				for (k = k + 1; s1[k] != '/'; k++)
				{
					a = a * 10 + s1[k] - 48;
				}
				ftData[kk][i] = a;

				a = 0;
				for (k = k + 1; s1[k]; k++)
				{
					a = a * 10 + s1[k] - 48;
				}
				fnData[kk][i] = a;
			}
			mtlData[kk] = mtl;
			kk++;

		}
		else if (content[0] == 'u' && content[1] == 's')
		{
			std::istringstream iss(content);
			iss >> s1 >> mtl;
		}
	}
	ifs.close();
}
