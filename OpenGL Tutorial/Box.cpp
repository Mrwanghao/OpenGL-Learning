#include "Box.h"



Box::Box()
{
	m_VertexArray = new Renderer::VertexArray();

	GLfloat vertices[] =
	{
		 0.5f,  0.5f,  0.5f, //0
		 0.5f, -0.5f,  0.5f, //1
		-0.5f,  0.5f,  0.5f, //2
		-0.5f, -0.5f,  0.5f, //3
		 0.5f,	0.5f, -0.5f, //4
		 0.5f, -0.5f, -0.5f, //5
		-0.5f,  0.5f, -0.5f, //6
		-0.5f, -0.5f, -0.5f, //7
	};
	m_VertexArray->addBuffer(new Renderer::Buffer(vertices, 8 * 3, 3), 0);

	GLfloat coordinates[] =
	{
		0.0f
	};
	m_VertexArray->addBuffer(new Renderer::Buffer(coordinates, 24 * 2, 2), 1);

	GLfloat normals[] =
	{
		0.0f,
	};
	m_VertexArray->addBuffer(new Renderer::Buffer(normals, 24 * 3, 3), 2);

	GLushort indices[] =
	{
		0,
	};
	m_IndexBuffer = new Renderer::IndexBuffer(indices, 24);

}

Box::~Box()
{
	if (m_VertexArray)
	{
		delete m_VertexArray;
	}
	m_VertexArray = nullptr;

	if (m_IndexBuffer)
	{
		delete m_IndexBuffer;
	}
	m_IndexBuffer = nullptr;
}

void Box::draw() const
{


}
