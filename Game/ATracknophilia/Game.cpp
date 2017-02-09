#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_camera(Rect(Vector2D(0,0), windowSize), 1.0f)
{
	m_camera.setLevelSize(levelSize);
	m_renderer.init(windowSize, windowName, &m_camera);
}

void Game::init()
{
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new Command(std::bind(&Camera2D::decreaseScale, &m_camera), EventListener::Type::Press));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new Command(std::bind(&Camera2D::increaseScale, &m_camera), EventListener::Type::Press));
}

void Game::update(float dt)
{
}

void Game::render()
{
	m_renderer.clear(Colour(0,0,0));

	m_renderer.drawRect(Rect(Vector2D(0, 0), Vector2D(100, 100)), Colour());

	m_renderer.present();
}
