#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "Player.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_resourceMgr(nullptr)
{
	new Player(0);
	m_renderer.init(windowSize, windowName, &m_camera);
	m_camera.init(windowSize.w, windowSize.h, m_renderer.getRenderer());

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
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, -1), EventListener::Type::Press));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, 1), EventListener::Type::Press));

	m_resourceMgr = ResourceManager::getInstance();
	m_resourceMgr->init(&m_renderer);
	m_resourceMgr->loadResources("..//..//assets//resources.json");
	m_resourceMgr->loadResourceQueue();
}

void Game::loop(float dt)
{
	World().Step(dt, 6, 3);
	for (auto& system : m_systems)
	{
		system->process();
	}
}
