#include "Texture2D.h"
#include "stb_image.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

	extern Renderer::Camera mCamera;

namespace Renderer
{

	Texture2D::Texture2D(std::string pTexFileName)
		:
	mShader(new Shader("texture.vs", "texture.fs"))
	{
		init_buffers();

		load_image(pTexFileName);
	}

	Texture2D::~Texture2D()
	{
	}

	
	//³õÊ¼»¯vertexarray ºÍ buffers
	void Texture2D::init_buffers()
	{
		mVertexArray = new VertexArray();

		GLfloat vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		};
		mVertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

		GLfloat colors[] =
		{
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
		};
		mVertexArray->addBuffer(new Buffer(colors, 4 * 3, 3), 1);

		GLfloat texcoords[] =
		{
			0.0f, 0.0f, 
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};
		mVertexArray->addBuffer(new Buffer(texcoords, 4 * 2, 2), 2);

		GLuint indices[] =
		{ 
			0, 1, 2,
			2, 3, 0,
		};
		mIndexBuffer = new IndexBuffer(indices, 6);
	}


	void Texture2D::enable() const
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	void Texture2D::disable() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::draw(const Window &mWindow) const
	{
		mVertexArray->enable();
		mIndexBuffer->enable();
		
		mShader->enable();

		glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)mWindow.mWidth / (float)mWindow.mHeight, 0.1f, 100.0f);
		mShader->setMat4("projection", projection);

		glm::mat4 view = mCamera.GetViewMatrix();
		mShader->setMat4("view", view);

#if 0
		glm::mat4 model;
		model = glm::rotate(model, (float)glfwGetTime() * 5, glm::vec3(0, 1.0f, 0));
		mShader->setMat4("model", model);
#endif

		glDrawElements(GL_TRIANGLES, mIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);
		
		mShader->disable();

		mIndexBuffer->disable();
		mVertexArray->disable();
		
	}

}
