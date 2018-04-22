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
	class Terrain
	{
	public:
		Terrain();
		~Terrain();

	public:
		void loadHeightMap(const char * fileName);
		void setBuffers();
		void draw(const Window &mWindow) const;

	private:
		VertexArray *mVertexArray;
		Shader *mShader;
		unsigned char *_heightData;
		std::vector<glm::vec3> mVertices;

	};

}
