#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "Player.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_camera(Rect(Vector2D(0,0), windowSize), 1.0f)
{
	new Player(0);
	m_camera.setLevelSize(levelSize);
	m_renderer.init(windowSize, windowName, &m_camera);

	auto syncSys = new SyncSystem();
	auto inputSys = new InputSystem();
	auto renderSys = new RenderSystem();
	renderSys->init(&m_renderer);

	m_systems.push_back(syncSys);
	m_systems.push_back(inputSys);

	//render system must be added last
	m_systems.push_back(renderSys);
}

void Game::init()
{
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new Command(std::bind(&Camera2D::decreaseScale, &m_camera), EventListener::Type::Press));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new Command(std::bind(&Camera2D::increaseScale, &m_camera), EventListener::Type::Press));
}

void Game::loop(float dt)
{
	for (auto& system : m_systems)
	{
		system->process();
	}
}

