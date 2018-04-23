#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"
#include <vector>
#include <glm/vec3.hpp>
#include "BMPImage.h"




namespace Renderer
{
	struct TerrainVec3 {
		float x, y, z;
		TerrainVec3(float _x, float _y, float _z)
			:
			x(_x),
			y(_y),
			z(_z)
		{
		}
	};

	class Terrain
	{
	public:
		Terrain();
		~Terrain();

	public:
		void loadHeightMap(const char * fileName);
		void draw(const Window &mWindow) const;
		void setSize(int _width, int _cellWidth);
		void setDataToBuffer();

	private:
		VertexArray *mVertexArray;
		Shader *mShader;
		BYTE *mHeightData;
		int mWidth;
		int mCellWidth;
		std::vector<float> _vertices;

	private:
		int GetHeight(int _x, int _y);
	};

}
