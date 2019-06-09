#pragma once

#include "OBJLoader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class MtlAndObjModel
{
public:
	MtlAndObjModel(const char *mtlFileName, const char *objFileName, int vtNumber);
	~MtlAndObjModel();

private:
	OBJLoader * objLoader;
	VertexArray *mVertexArray;
	IndexBuffer *mIndexBuffer;

private:
	void setDataToBuffer();
};

