#include "Buffer.h"
#include "Mesh.h"

namespace Renderer
{

	Buffer::Buffer(GLfloat *pData, GLsizei pCount, GLuint pComponentCount)
		:
		mComponentCount(pComponentCount),
		mCount(pCount)
	{
		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, pCount * sizeof(GLfloat), pData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(void *pData, GLsizei pCount)
		:
		mComponentCount(0)
	{
		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, pCount * sizeof(Vertex), pData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(std::vector<float> &data, GLsizei count, GLuint componentCount)
		:
		mComponentCount(componentCount)
	{
		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &mBufferID);
	}

}
