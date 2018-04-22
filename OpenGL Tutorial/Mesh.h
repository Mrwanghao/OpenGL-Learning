#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace Renderer
{
	struct Vertex 
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct Texture 
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh 
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();

	public:
		void Draw(const Shader *shader);
		bool loadMesh(std::string &fileName);

	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

	private:
		void setupMesh();

	private:
#if 0
		GLuint VAO;
		GLuint VBO, EBO;
#else
		VertexArray *mVertexArray;
		IndexBuffer *mIndexBuffer;
#endif

	};

}
