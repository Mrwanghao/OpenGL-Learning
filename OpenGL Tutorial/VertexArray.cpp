#include "VertexArray.h"
#include "Mesh.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mVertexArrayID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mVertexArrayID);
	for (size_t i = 0; i < mBuffers.size(); i++)
	{
		delete mBuffers[i];
	}	
}

void VertexArray::addBuffer(Buffer * pBuffer, GLuint pIndex)
{
	enable();
	pBuffer->enable();
		
	glVertexAttribPointer(pIndex, pBuffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pIndex);
		
	mBuffers.push_back(pBuffer);

	pBuffer->disable();
	disable();
}

void VertexArray::addBuffer(Buffer * pBuffer, GLuint pIndex, GLuint pCount, size_t pTotalSize, void *pData, bool pIsPushBack)
{
	enable();
	pBuffer->enable();

	glEnableVertexAttribArray(pIndex);
	glVertexAttribPointer(pIndex, pCount, GL_FLOAT, GL_FALSE, pTotalSize, pData);
		
	if (pIsPushBack)
	{
		mBuffers.push_back(pBuffer);
	}

	pBuffer->disable();
	disable();
}
