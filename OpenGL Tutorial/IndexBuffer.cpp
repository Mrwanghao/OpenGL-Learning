#include "IndexBuffer.h"


namespace Renderer
{
	IndexBuffer::IndexBuffer(GLuint *pData, GLsizei pCount)
		:
	mCount(pCount)
	{
		glGenBuffers(1, &mIndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pCount * sizeof(GLuint), pData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mIndexBufferID);
	}
};