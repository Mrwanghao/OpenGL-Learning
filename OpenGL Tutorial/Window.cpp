#include "Window.h"
#include "Timer.h"


float mDeltaTime = 0.0f;

Window::Window(unsigned int pWidth, unsigned int pHeight, std::string pTitle)
	:
	mWidth(pWidth),
	mHeight(pHeight),
	mTitle(pTitle)
{
	if (!init())
	{
		std::cout << "window init error." << std::endl;
	}
}

bool Window::closed() const
{
	return glfwWindowShouldClose(mWindow) == 1 ? true : false;
}

void Window::update() const
{
	processInput(mWindow);
		
	mDeltaTime = Timer::getDeltaTime();

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void Window::clear() const
{
	glClearColor(0.1f, 0.5f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::getMousePosition(double * x, double * y)
{
	glfwGetCursorPos(mWindow, x, y); 
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
	if (!mWindow)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	glfwSetWindowSizeCallback(mWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(mWindow, mouse_callback);
	glfwSetScrollCallback(mWindow, scroll_callback);

	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_MULTISAMPLE);
		

	return true;
}

