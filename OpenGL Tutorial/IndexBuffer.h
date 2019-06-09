#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class IndexBuffer
{
public:
	IndexBuffer(GLushort *pData, GLint pCount);
	~IndexBuffer();

public:
	inline void enable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID); }
	inline void disable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	inline GLint getCount() const { return mCount; }


private:
	void bindData(GLushort *pData, GLint pCount);
	unsigned short* m_Data;
	GLuint mIndexBufferID;
	GLint mCount;
};
