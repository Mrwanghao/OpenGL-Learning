#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineEnum.h"
#include <glm/vec3.hpp>

namespace Renderer 
{

	struct Vertex;
	
	class Buffer
	{
	public:
		Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
		Buffer(void *data, GLsizei count);
		~Buffer();

	public:
		inline void enable() const { glBindBuffer(GL_ARRAY_BUFFER, mBufferID); }
		inline void disable() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		inline GLuint getComponentCount() const { return mComponentCount; }

	private:
		GLuint mBufferID;
		GLuint mComponentCount;
	};
};

