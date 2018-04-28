#include "IndexBuffer.h"
#include <stdlib.h>
#include <iostream>

namespace Renderer
{
	IndexBuffer::IndexBuffer(GLushort *pData, GLint pCount)
		:
	mCount(pCount)
	{
		bindData(pData, mCount);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mIndexBufferID);
	}

	void IndexBuffer::bindData(GLushort * pData, GLint pCount)
	{

		glGenBuffers(1, &mIndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pCount * sizeof(GLushort), pData, GL_STATIC_DRAW);
		free(m_Data);
		m_Data = (unsigned short*)malloc(sizeof(unsigned short) * mCount);
		m_Data = pData;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};