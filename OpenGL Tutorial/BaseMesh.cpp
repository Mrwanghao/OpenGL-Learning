#include "BaseMesh.h"

BaseMesh::BaseMesh()
	:
	mVertexArray(new VertexArray())
{

}




BaseMesh::~BaseMesh()
{
	if (mVertexArray) delete mVertexArray; mVertexArray = nullptr;
	if (mIndexBuffer) delete mIndexBuffer; mIndexBuffer = nullptr;

}

void BaseMesh::draw() const
{
}
