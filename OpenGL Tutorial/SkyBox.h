#pragma once
#include <glad/glad.h>

#include "stb_image.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Window.h"
#include <vector>
#include <string>


namespace Renderer {

	class SkyBox
	{
	public:
		SkyBox();
		~SkyBox();

	private:
		VertexArray * m_vertexArray;
		Buffer * m_positionBuffer;
		Shader *m_shader;

	private:
		void init_attributes();

	public:
		void draw(Window _window);
	};

}
