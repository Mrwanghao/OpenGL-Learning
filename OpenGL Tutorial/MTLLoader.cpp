#include "MTLLoader.h"
#include "Material.h"
#include "MaterialManager.h"
#include <fstream>
#include "ImageSet.h"
#include <sstream>
#include <iostream>
#include <stdio.h>

MTLLoader::MTLLoader(const char *_mtlFileName)
	:
	mtlFileName(_mtlFileName),
	mtlCount(0)
{
}


MTLLoader::~MTLLoader()
{
}

//init mtlCount
void MTLLoader::ReadMTLInfo()
{
	std::ifstream inFileStream(mtlFileName);
	std::string fileContent;
	while (getline(inFileStream, fileContent))
	{
		if (fileContent[0] == 'n' && fileContent[1] == 'e')
		{
			mtlCount++;
		}
	}
	inFileStream.close();
}

void MTLLoader::ReadMTLFile()
{
	std::ifstream inFileStream(mtlFileName);
	std::string fileContent;

	int n = 0, t = 0, d = 0, a = 0, s = 0;

	std::string value, name, texture;
	float red = 0, green = 0, blue = 0;

	Material *mtl = nullptr;

	while (getline(inFileStream, fileContent))
	{
		if (fileContent != "")
		{

			std::istringstream iss(fileContent);
			iss >> value;

			if (value == "newmtl")
			{
				iss >> name;
				mtl = new Material(name.c_str());
				objMtlMap[mtl->name] = MaterialManager::Instance->add(mtl);
				n++;
			}
			else if (value == "map_Kd")
			{
				iss >> texture;
				if (mtl)
				{
					
				}


			}

		}

	}


}
