#pragma once


#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Batch
{
	VertexArray *m_VertexArray;
	IndexBuffer *m_IndexBuffer;

	void draw() const;
	void pushDataToBuffer(GLfloat *data);
};