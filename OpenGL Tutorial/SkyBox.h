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
		std::vector<std::string> mFacesFileName;
	private:
		void initAttributes();
		inline void enable() const { glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeTexturesID); }
		inline void disable() const { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

	public:
		void draw();
		
	};

}
