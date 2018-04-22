#pragma once
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



class MTLLoader
{
public:
	MTLLoader(const char *_mtlFileName);
	~MTLLoader();

private:
	const char *mtlFileName;
	unsigned int mtlCount;

private:
	void ReadMTLInfo();
	void ReadMTLFile();
};

