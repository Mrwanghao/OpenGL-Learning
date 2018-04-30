#pragma once
#include <glad/glad.h>

#include "VertexArray.h"
#include "Shader.h"
#include <vector>
#include <string>


namespace Renderer {

	class SkyBox
	{
	public:
		SkyBox();
		~SkyBox();

	private:
		VertexArray * mVertexArray;
		Shader *mShader;
		GLuint mCubeTexturesID;

	private:
		void initAttributes();
		void initCubeTextures();

	public:
		void draw();
	};

}
