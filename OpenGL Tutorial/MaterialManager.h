#pragma once

#include <map>
#include <vector>
#include "Material.h"

#define DEFAULT_MATERIAL "default_material"
#define BLACK_MATERIAL "black_material"


class MaterialManager
{
public:
	static MaterialManager *Instance;

	static void Init();
	static void Release();

private:
	std::vector<Material*> materialVector;
	std::map<std::string, Material*> materialMap;

public:
	MaterialManager();
	~MaterialManager();

public:
	unsigned int add(Material *_material);
	void remove(unsigned int _index);
	Material* find(unsigned int index);
	int find(std::string _name);
	unsigned int size();
};

