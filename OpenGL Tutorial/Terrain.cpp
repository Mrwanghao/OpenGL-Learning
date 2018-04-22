#include "Terrain.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


	extern Renderer::Camera mCamera;

namespace Renderer
{

	Terrain::Terrain()
		:
	mShader(new Shader("Terrain.vs", "Terrain.fs"))
	{

		

	}


	Terrain::~Terrain()
	{
		delete mVertexArray;
		delete mShader;
	}

	void Terrain::loadHeightMap(const char * fileName)
	{
		FILE* file = NULL;
		file = fopen(fileName, "rb");
		if (file == NULL)
			return;
		fread(_heightData, 1, 1024 * 1024, file);
		if (ferror(file))
			return;
		fclose(file);

	}

	void Terrain::setBuffers()
	{
		for (unsigned int row = 0; row < 1024 - 1; row++)
		{
			for (unsigned int col = 0; col < 1024 - 1; col++)
			{
				glm::vec3 v1(col + 0, _heightData[(row * 1024 + col)], row + 0);
				glm::vec3 v2(col + 0, _heightData[((row + 1) * 1024 + col)], row + 1);
				glm::vec3 v3(col + 1, _heightData[((row + 1) * 1024 + col + 1)], row + 1);
				glm::vec3 v4(col + 1, _heightData[(row * 1024 + col + 1)], row + 0);


				mVertices.push_back(v1);
				mVertices.push_back(v2);
				mVertices.push_back(v3);
				mVertices.push_back(v1);
				mVertices.push_back(v3);
				mVertices.push_back(v4);
			}
		}

		
	}

	void Terrain::draw(const Window &mWindow) const
	{
		mVertexArray->enable();
		mShader->enable();

		glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)mWindow.mWidth / (float)mWindow.mHeight, 0.1f, 100.0f);
		mShader->setMat4("projection", projection);

		glm::mat4 view = mCamera.GetViewMatrix();
		mShader->setMat4("view", view);

		glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

		mShader->disable();
		mVertexArray->disable();
	}
}
