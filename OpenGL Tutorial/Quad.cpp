#include "Quad.h"
#include "Buffer.h"

Quad::Quad()
{


}


Quad::~Quad()
{
}

void Quad::initBufferAndVertexArray()
{
	GLfloat vertices[] =
	{
		// positions         
		5.0f, -0.5f,  5.0f,  
		-5.0f, -0.5f,  5.0f, 
		-5.0f, -0.5f, -5.0f, 

		5.0f, -0.5f,  5.0f,  
		-5.0f, -0.5f, -5.0f, 
		5.0f, -0.5f, -5.0f,  
	};
	mVertexArray->addBuffer(new Buffer(vertices, 6 * 3, 3), 0);
	
	GLfloat texcoords[] =
	{
		// texture Coords 
		2.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 2.0f,

		2.0f, 0.0f,
		0.0f, 2.0f,
		2.0f, 2.0f
	};
	mVertexArray->addBuffer(new Buffer(texcoords, 6 * 2, 2), 1);

	mIndexBuffer = nullptr;
}

void Quad::draw()
{
	mVertexArray->enable();
	mIndexBuffer->enable();

	glDrawElements(GL_TRIANGLES, mIndexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);

	mIndexBuffer->disable();
	mVertexArray->disable();

}



