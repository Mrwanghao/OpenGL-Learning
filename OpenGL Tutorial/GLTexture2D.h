#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GLTexture2D
{
	GLuint m_TextureID;
	GLuint m_Width, m_Height;
	GLuint m_InternalFormat;
	GLuint m_ImageFormat;
	GLuint m_WrapT;
	GLuint m_WrapS;
	GLuint m_FilterMin;
	GLuint m_FilterMax;

public:
	GLTexture2D();
	~GLTexture2D();

	void generate(GLuint _width, GLuint _height,unsigned char* data);
	void enable() const;

};
