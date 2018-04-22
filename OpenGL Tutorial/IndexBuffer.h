#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer
{
	class IndexBuffer
	{
	public:
		IndexBuffer(GLuint *pData, GLsizei pCount);
		~IndexBuffer();

	public:
		inline void enable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID); }
		inline void disable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline GLsizei getCount() const { return mCount; }

	private:
		GLuint mIndexBufferID;
		GLsizei mCount;
	};

};