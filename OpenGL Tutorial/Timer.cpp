#include "Timer.h"
#include <GLFW/glfw3.h>

namespace Time
{
	float Timer::deltaTime = 0.0f;
	float Timer::lastFrame = 0.0f;

	Timer::Timer()
	{
	
	}


	Timer::~Timer()
	{

	}
	
	float Timer::getDeltaTime()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		return deltaTime;
	}
	
}
