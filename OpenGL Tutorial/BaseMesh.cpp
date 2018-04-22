#include "BaseMesh.h"


BaseMesh::BaseMesh()
	:
	vertexCount(0),
	indexCount(0),
	materials(nullptr),
	vertices(nullptr),
	indices(nullptr),
	normals(nullptr),
	texcoords(nullptr)
{

}

BaseMesh::BaseMesh(const BaseMesh & ths)
{
}


BaseMesh::~BaseMesh()
{
	if (materials) delete materials; materials = nullptr;
	if (vertices) delete vertices; vertices = nullptr;
	if (normals) delete normals; normals = nullptr;
	if (texcoords) delete texcoords; texcoords = nullptr;
	if (indices) delete indices; indices = nullptr;

}