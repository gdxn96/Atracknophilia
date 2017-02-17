#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "LevelLoader.h"
#include "EntityFactory.h"
#include "DirectionVolume.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_resourceMgr(ResourceManager::getInstance())
{
	LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
		{LEVELS::PROTOTYPE, "..\\..\\Prototype\\ATracknophilia\\levels\\test.json"}, 
	});

	m_renderer.init(windowSize, windowName, &m_camera);

	m_camera.init(windowSize.w, windowSize.h, m_renderer.getRenderer());
	m_camera.setZoomMinMax(-1, 0.2);

	//Declare systems
	auto inputSys = new InputSystem();
	auto renderSys = new RenderSystem();
	auto collisionSystem = new CollisionSystem();
	auto physicsSystem = new PhysicsSystem();
	auto cameraSystem = new CameraSystem();
	auto hookSys = new HookSystem();

	EntityFactory::SpawnPlayer(60, 60, 10, 10);
	EntityFactory::SpawnPlayer(120, 60, 10, 10);

	//Init systems
	renderSys->init(&m_renderer);
	cameraSystem->init(&m_camera);
	
	//Push back systems
	m_systems.push_back(inputSys);
	m_systems.push_back(collisionSystem);
	m_systems.push_back(inputSys);
	m_systems.push_back(hookSys);
	m_systems.push_back(physicsSystem);
	m_systems.push_back(cameraSystem);
	//render system must be added last
	m_systems.push_back(renderSys);

	//temp stuff
	//auto DirectionEntity = new DirectionVolume(88, 50, 0, 110, 600, 0, Vector2D(0, 1));
	//auto DirectionEntity2 = new DirectionVolume(89, 50, 600, 1000, 100, 1, Vector2D(1, 0));
}

void Game::init()
{
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, -1)));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, 1)));

	m_resourceMgr->init(&m_renderer);
	m_resourceMgr->loadResources("..//..//assets//resources.json");
	m_resourceMgr->loadResourceQueue();

	LevelLoader::loadLevel(LEVELS::PROTOTYPE);
}

void Game::loop(float dt)
{
	for (auto& system : m_systems)
	{
		system->process(dt);
	}
}
