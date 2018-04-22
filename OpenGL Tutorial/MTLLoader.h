#pragma once
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>


class MTLLoader
{
public:
	MTLLoader(const char *_mtlFileName);
	~MTLLoader();

private:
	const char *mtlFileName;
	unsigned int mtlCount;

public:
	std::map<std::string, int> objMtlMap;

private:
	void ReadMTLInfo();
	void ReadMTLFile();
};

