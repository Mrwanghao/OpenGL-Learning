#include "Game.h"

Game::Game(GLuint _width, GLuint _height)
	:
	m_GameState(GAME_ACTIVE),
	m_Keys(),
	m_Width(_width),
	m_Height(_height)
{
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
}
