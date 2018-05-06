#include "SkyBox.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Window.h"
	extern System::Camera mCamera;
	extern Renderer::Window mWindow;

namespace Renderer {

	SkyBox::SkyBox()
		:
		mShader(new Shader("SkyBox.vs", "SkyBox.fs")),
		mVertexArray(new VertexArray())
	{
		mFacesFileName.push_back("right.jpg");
		mFacesFileName.push_back("left.jpg");
		mFacesFileName.push_back("top.jpg");
		mFacesFileName.push_back("bottom.jpg");
		mFacesFileName.push_back("front.jpg");
		mFacesFileName.push_back("back.jpg");
		initAttributes();
		mShader->enable();
		mShader->setInt("skybox", 0);
	}


	SkyBox::~SkyBox()
	{
		mFacesFileName.clear();
		if (mVertexArray) delete mVertexArray; mVertexArray = nullptr;
		if (mShader) delete mShader; mShader = nullptr;
	}

	void SkyBox::initAttributes()
	{
		GLfloat skyboxVertices[] = {
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

		mVertexArray->addBuffer(new Buffer(skyboxVertices, 6 * 6 * 3, 3), 0);

		mCubeTexturesID = load_cube_map(mFacesFileName);
	}


	void SkyBox::draw()
	{

		glDepthFunc(GL_LEQUAL);
		enable();
		mVertexArray->enable();
		mShader->enable();

		glActiveTexture(GL_TEXTURE0);
		glm::mat4 view = glm::mat4(glm::mat3(mCamera.GetViewMatrix()));
		glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)mWindow.mWidth / (float)mWindow.mHeight, 0.1f, 100.0f);
		mShader->setMat4("view", view);
		mShader->setMat4("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		mShader->disable();
		mVertexArray->disable();
		disable();
		glDepthFunc(GL_LESS);
	}

	

}
