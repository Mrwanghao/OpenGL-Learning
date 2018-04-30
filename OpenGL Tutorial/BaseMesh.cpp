#include "BaseMesh.h"

using namespace Renderer;

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
