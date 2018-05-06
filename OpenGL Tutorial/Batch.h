#pragma once


#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Batch
{
	Renderer::VertexArray *m_VertexArray;
	Renderer::IndexBuffer *m_IndexBuffer;

	void draw() const;
	void pushDataToBuffer(GLfloat *data);
};