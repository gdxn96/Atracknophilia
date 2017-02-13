#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "LevelLoader.h"
#include "EntityFactory.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_resourceMgr(nullptr)
{
	LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
		{LEVELS::PROTOTYPE, "..\\..\\Prototype\\ATracknophilia\\levels\\test.json"}, 
	});

	m_renderer.init(windowSize, windowName, &m_camera);
	m_camera.init(windowSize.w, windowSize.h, m_renderer.getRenderer());
	

	auto inputSys = new InputSystem();
	auto renderSys = new RenderSystem();
	auto physicsSystem = new PhysicsSystem();
	renderSys->init(&m_renderer);

	m_systems.push_back(inputSys);
	m_systems.push_back(physicsSystem);

	//render system must be added last
	m_systems.push_back(renderSys);

	EntityFactory::SpawnPlayer(60, 60, 10, 10);
	EntityFactory::SpawnPlayer(120, 60, 10, 10);

	m_camera.setZoomProps(0.01f, 1.0f, 1.0f, 0.01f);
	//m_camera.zoomTo(60, 60);
	//m_camera.setCentre(60, 60);
}

void Game::init()
{
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, -1), EventListener::Type::Press));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, 1), EventListener::Type::Press));

	m_resourceMgr = ResourceManager::getInstance();
	m_resourceMgr->init(&m_renderer);
	m_resourceMgr->loadResources("..//..//assets//resources.json");
	m_resourceMgr->loadResourceQueue();

	LevelLoader::loadLevel(LEVELS::PROTOTYPE);
}

void Game::loop(float dt)
{
	//m_camera.zoomTo(60, 60);
	for (auto& system : m_systems)
	{
		system->process(dt);
	}
}
