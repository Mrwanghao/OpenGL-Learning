#include "Batch.h"

void Batch::draw() const
{
	m_VertexArray->enable();
	m_IndexBuffer->enable();

	glDrawElements(GL_TRIANGLES, m_IndexBuffer->getCount(), GL_UNSIGNED_INT, 0);

	m_IndexBuffer->disable();
	m_VertexArray->disable();

}

void Batch::pushDataToBuffer(GLfloat *data)
{

}
