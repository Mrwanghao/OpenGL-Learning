#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "Camera.h"
#include "Common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {

	using namespace System;

	extern float mDeltaTime;

	class Window
	{
	public:
		Window(unsigned int pWidth, unsigned int pHeight, std::string pTitle);
		~Window();

	public:
		bool closed() const;
		void update() const;
		void clear() const;
		void getMousePosition(double *x, double *y);
		inline void enableDepth() { glEnable(GL_DEPTH_TEST); }
		inline void disableDepth() { glDisable(GL_DEPTH_TEST); }

	private:
		bool init();

	public:
		unsigned int mWidth;
		unsigned int mHeight;

	private:
		std::string mTitle;
		GLFWwindow *mWindow;

	};

}
#endif // !_WINDOW_H_
