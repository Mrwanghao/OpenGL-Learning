#include "AssetsManager.h"

AssetsManager* AssetsManager::assetsManager = nullptr;

AssetsManager::AssetsManager()
{
	textures = new ImageSet();
}


AssetsManager::~AssetsManager()
{
	if (textures) delete textures; textures = nullptr;
}

void AssetsManager::Init()
{
	if (!assetsManager)
	{
		assetsManager = new AssetsManager();
	}
}

void AssetsManager::Release()
{
	if (assetsManager) delete assetsManager; assetsManager = nullptr;
}

void AssetsManager::addTexture(const char * name)
{
	textures->addTexture(name);
}

int AssetsManager::findTexture(const char * name)
{
	return textures->findTexture(name);
}

void AssetsManager::initTexturesArray()
{
	
}
