#include "Renderable2D.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

namespace Renderer
{

	Renderable2D::Renderable2D(glm::vec3 &pPosition, glm::vec2 &pSize, glm::vec4 &pColor, Shader *pShader)
		:
		mPosition(pPosition),
		mSize(pSize),
		mColor(pColor),
		mShader(pShader)
	{

		mVertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, mSize.y, 0,
			mSize.x, mSize.y, 0,
			mSize.x, 0, 0
		};
		mVertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

		GLfloat colors[] =
		{
			mColor.x, mColor.y, mColor.z,
			mColor.y, mColor.z, mColor.x,
			mColor.z, mColor.x, mColor.y,
			mColor.x, mColor.y, mColor.z
		};
		mVertexArray->addBuffer(new Buffer(colors, 4 * 3, 3), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		mIndexBuffer = new IndexBuffer(indices, 6);
	}


	Renderable2D::~Renderable2D()
	{
		delete mVertexArray;
		delete mIndexBuffer;
	}
}
