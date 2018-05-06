#pragma once
#include "ImageSet.h"
class AssetsManager
{
public:
	static AssetsManager* assetsManager;

public:
	AssetsManager();
	~AssetsManager();

	static void Init();
	static void Release();

public:
	ImageSet * textures;

public:
	void addTexture(const char *name);
	int findTexture(const char *name);
	void initTexturesArray();
};

