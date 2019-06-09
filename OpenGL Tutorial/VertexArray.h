#pragma once

#include <glad/glad.h>

#include <vector>
#include "Buffer.h"


struct Vertex;

class VertexArray
{
private:
	GLuint mVertexArrayID;
	std::vector<Buffer*> mBuffers;
public:
	VertexArray();
	~VertexArray();

public:
	inline void enable() const { glBindVertexArray(mVertexArrayID); }
	inline void disable() const { glBindVertexArray(0); }
		
	void addBuffer(Buffer *pBuffer, GLuint pIndex);
	void addBuffer(Buffer *pBuffer, GLuint pIndex, GLuint pCount, size_t pTotalSize, void *pData, bool pIsPushBack = false);
};

