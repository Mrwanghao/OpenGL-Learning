#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glad/glad.h>

#include "VertexArray.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "BaseMesh.h"

class Box : public BaseMesh
{
	Box();
	~Box();

	Renderer::VertexArray *m_VertexArray;
	Renderer::IndexBuffer *m_IndexBuffer;

public:
	void draw() const;

};
