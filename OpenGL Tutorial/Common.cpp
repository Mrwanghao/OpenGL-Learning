#include "Common.h"
#include "Window.h"
#include "stb_image.h"

	extern Renderer::Camera mCamera;
	extern enum Camera_Movement;

	extern float Renderer::mDeltaTime;
	bool firstMouse = false;
	double lastX = 0.0f;
	double lastY = 0.0f;

	void processInput(GLFWwindow *pWindow)
	{
		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(pWindow, true);
		}

		if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
			mCamera.ProcessKeyboard(System::Camera_Movement::FORWARD, Renderer::mDeltaTime);
		if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
			mCamera.ProcessKeyboard(System::Camera_Movement::BACKWARD, Renderer::mDeltaTime);
		if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
			mCamera.ProcessKeyboard(System::Camera_Movement::LEFT, Renderer::mDeltaTime);
		if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
			mCamera.ProcessKeyboard(System::Camera_Movement::RIGHT, Renderer::mDeltaTime);
		
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		mCamera.ProcessMouseMovement(xoffset, yoffset);
		
	}


	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mCamera.ProcessMouseScroll(yoffset);

	}

	void framebuffer_size_callback(GLFWwindow *pWindow, int pWidth, int pHeight)
	{
		glViewport(0, 0, pWidth, pHeight);

	}

	GLuint load_image(std::string pTexFileName)
	{
		GLuint mTextureID;
		glGenTextures(1, &mTextureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(pTexFileName.c_str(), &width, &height, &nrComponents, 0);

		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		if (data)
		{

			glBindTexture(GL_TEXTURE_2D, mTextureID);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << pTexFileName << std::endl;
		}
		stbi_image_free(data);
		
		

		return mTextureID;
	}

	GLuint load_cube_map(std::vector<std::string> p_faces)
	{
		GLuint _textureID;
		glGenTextures(1, &_textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < p_faces.size(); i++)
		{
			unsigned char *data = stbi_load(p_faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << p_faces[i] << std::endl;
			}
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return _textureID;
	}


	
