#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glad/glad.h>

#include "BaseMesh.h"
#include "Window.h"

class Box : public BaseMesh
{
	Box();
	~Box();


public:
	void draw() const;
	virtual void initBufferAndVertexArray();
};
