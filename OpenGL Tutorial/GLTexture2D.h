#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef TEXTURE_TYPE_COLOR
#define TEXTURE_TYPE_COLOR 1
#define TEXTURE_TYPE_DEPTH 2
#define LOW_PRE 0
#define HIGH_PRE 1
#endif // !TEXTURE_TYPE_COLOR


class GLTexture2D
{
	GLuint textureID;
	float width, height;
	int type;
	int precision;

public:
	GLTexture2D(float _width, float _height, int _type, int _precision);
	~GLTexture2D();

private:
	void init();

};
