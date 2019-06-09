#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"
#include <vector>
#include <glm/vec3.hpp>
#include "BMPImage.h"



class Terrain
{
public:
	Terrain(const char *fileName);
	~Terrain();

public:
	void loadHeightMap(const char * fileName);
	void draw() const;
	void setSize(int _width, int _cellWidth);
	void addTexture(const char *fileName);

private:
	VertexArray *mVertexArray;
	Shader *mShader;
	BYTE *mHeightData;
	int mWidth;
	int mCellWidth;
	std::vector<float> _vertices;
	std::vector<float> _texcoords;
	std::vector<GLuint> _textureIDs;
private:
	void setDataToBuffer();
	int GetHeight(int _x, int _y);
};


