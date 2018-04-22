#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class BaseMesh
{
private:
	virtual void initFaces() = 0;

public:
	BaseMesh();
	BaseMesh(const BaseMesh& ths);
	virtual ~BaseMesh();

public:
	int vertexCount;
	int indexCount;
	glm::vec4 *vertices;
	glm::vec3 *normals;
	glm::vec2 *texcoords;
	int *materials;
	int *indices;

};

