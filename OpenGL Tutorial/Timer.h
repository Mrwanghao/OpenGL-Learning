#pragma once


class Timer
{
public:
	Timer();
	~Timer();

public:
	static float getDeltaTime();

private:
	static float deltaTime;
	static float lastFrame;
};


