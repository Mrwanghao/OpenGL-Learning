#include "GLTexture2D.h"

GLTexture2D::GLTexture2D()
	:
	m_Width(0),
	m_Height(0),
	m_InternalFormat(GL_RGB),
	m_ImageFormat(GL_RGB),
	m_WrapS(GL_REPEAT),
	m_WrapT(GL_REPEAT),
	m_FilterMax(GL_LINEAR),
	m_FilterMin(GL_LINEAR)

{
	glGenTextures(1, &m_TextureID);
}

GLTexture2D::~GLTexture2D()
{
}

void GLTexture2D::generate(GLuint _width, GLuint _height, unsigned char * data)
{
	this->m_Width = _width;
	this->m_Height = _height;

	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_InternalFormat, this->m_Width, this->m_Height, 0, this->m_ImageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_WrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_FilterMax);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_FilterMin);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void GLTexture2D::enable() const
{
	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
}
