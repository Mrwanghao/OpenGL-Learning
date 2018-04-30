#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "VertexArray.h"
#include "Buffer.h"
#include "IndexBuffer.h"

class BaseMesh
{

public:
	BaseMesh();
	virtual ~BaseMesh();

public:
	Renderer::VertexArray *mVertexArray;
	Renderer::IndexBuffer *mIndexBuffer;

private:
	virtual void initBufferAndVertexArray() = 0;

public:
	virtual void draw() const;

};

