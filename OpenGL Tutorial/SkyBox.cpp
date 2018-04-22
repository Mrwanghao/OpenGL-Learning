#include "SkyBox.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

	extern Renderer::Camera mCamera;

namespace Renderer {

	SkyBox::SkyBox()
		:
		m_shader(new Shader("../Shaders/SkyBox.vs", "../Shaders/SkyBox.fs"))
	{
		init_attributes();


	}


	SkyBox::~SkyBox()
	{
		delete m_vertexArray;
		delete m_positionBuffer;

	}

	void SkyBox::init_attributes()
	{

		m_vertexArray = new VertexArray();

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		m_positionBuffer = new Buffer(skyboxVertices, 6 * 6 * 3, 3);
		m_vertexArray->addBuffer(m_positionBuffer, 0);

		std::vector<std::string> faces
		{
			"skybox/right.jpg",
			"skybox/left.jpg",
			"skybox/top.jpg",
			"skybox/bottom.jpg",
			"skybox/front.jpg",
			"skybox/back.jpg",
		};

		m_shader->setInt("skybox", 0);


	}

	void SkyBox::draw(Window _window)
	{
		m_shader->enable();


		glm::mat4 model;
		glm::mat4 view = mCamera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)_window.mWidth / (float)_window.mHeight, 0.1f, 100.0f);
		m_shader->setMat4("model", model);
		m_shader->setMat4("view", view);
	}

	

}
