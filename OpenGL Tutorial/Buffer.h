#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineEnum.h"
#include <glm/vec3.hpp>
#include <vector>


struct Vertex;
struct TerrainVec3;
	
class Buffer
{
public:
	Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
	Buffer(void *data, GLsizei count);
	Buffer(std::vector<float> &data, GLsizei count, GLuint componentCount);
	~Buffer();

public:
	inline void enable() const { glBindBuffer(GL_ARRAY_BUFFER, mBufferID); }
	inline void disable() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	inline GLuint getComponentCount() const { return mComponentCount; }
	inline GLuint getCount() const { return mCount; }
private:
	GLuint mBufferID;
	GLuint mComponentCount;
	GLuint mCount;
};


