#pragma once

#include "EngineEnum.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
	GAMESTATE m_GameState;
	GLboolean m_Keys[1024];
	GLuint m_Width, m_Height;

public:
	Game(GLuint _width, GLuint _height);
	~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};