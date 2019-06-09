#pragma once

#include <glad/glad.h>
#include <string>
#include "SimpleRenderer2D.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "IndexBuffer.h"



class Texture2D
{
public:
	Texture2D(std::string pTexFileName);
	~Texture2D();

private:
	GLuint mTextureID;
	VertexArray *mVertexArray;
	IndexBuffer *mIndexBuffer;
	Shader *mShader;

private:
		
	void init_buffers();


public:
	void enable() const;
	void disable() const;
	void draw() const;

	Shader* getShader() const { return mShader; }
};

