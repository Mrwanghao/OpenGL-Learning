#include "MaterialManager.h"

MaterialManager* MaterialManager::Instance = nullptr;

void MaterialManager::Init()
{
	if (Instance == nullptr)
	{
		Instance = new MaterialManager();
	}
}

void MaterialManager::Release()
{
	if (Instance)
	{	
		delete Instance;
	}
	Instance = nullptr;
}

MaterialManager::MaterialManager()
{
	materialVector.clear();
	materialMap.clear();

	Material *defaultMaterial = new Material(DEFAULT_MATERIAL);
	add(defaultMaterial);

	Material *blackMaterial = new Material(BLACK_MATERIAL);
	blackMaterial->ambient = glm::vec3(0.0f);
	blackMaterial->diffuse = glm::vec3(0.0f);
	add(blackMaterial);

}


MaterialManager::~MaterialManager()
{
	for (unsigned int index = 0; index < materialVector.size(); index++)
	{
		delete materialVector[index];
	}

	materialVector.clear();
	materialMap.clear();

}

unsigned int MaterialManager::add(Material * _material)
{
	materialVector.push_back(_material);
	materialMap[_material->name] = _material;
	int materialID = materialVector.size() - 1;
	_material->id = materialID;
	return materialID;
}

void MaterialManager::remove(unsigned int _index)
{
	if (materialVector.size() < _index + 1)
	{
		return;
	}

	int oldMaterialID = materialVector[_index]->id;
	std::string odlName = materialVector[_index]->name;

	delete materialVector[_index];

	Material *mtlEmp = new Material(odlName.c_str());
	mtlEmp->id = oldMaterialID;
	materialVector[_index] = mtlEmp;
	materialMap[odlName] = mtlEmp;

}

Material * MaterialManager::find(unsigned int index)
{
	if (materialVector.size() < index + 1)
	{
		return nullptr;
	}
	return materialVector[index];
}

int MaterialManager::find(std::string _name)
{
	if (materialMap.count(_name) <= 0)
	{
		return 0;
	}
	return materialMap[_name]->id;
}

unsigned int MaterialManager::size()
{
	return materialVector.size();
}
