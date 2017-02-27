#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "LevelLoader.h"
#include "EntityFactory.h"
#include "DirectionVolume.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_resourceMgr(ResourceManager::getInstance())
{
	m_renderer.init(windowSize, windowName, &m_camera);
	m_camera.init(windowSize.w, windowSize.h, m_renderer.getRenderer());

	m_cameraManager = CameraManager();

	//Declare systems
	auto inputSys = new InputSystem();
	auto renderSys = new RenderSystem();
	auto collisionSystem = new CollisionSystem();
	auto physicsSystem = new PhysicsSystem();
	auto aiSystem = new AISystem();
	auto hookSys = new HookSystem();

	//Init systems
	renderSys->init(&m_renderer);
	m_cameraManager.init(&m_camera);
	
	//Push back systems
	m_systems.push_back(inputSys);
	m_systems.push_back(collisionSystem);
	m_systems.push_back(inputSys);
	m_systems.push_back(hookSys);
	m_systems.push_back(physicsSystem);
	m_systems.push_back(aiSystem);

	//render system must be added last
	m_systems.push_back(renderSys);

	m_resourceMgr->init(&m_renderer);
	m_resourceMgr->loadResources(".//assets//resources.json");
	m_resourceMgr->loadResourceQueue();

	//create scenes
	GameScene * gameScene = new GameScene();
	StartScene * startScene = new StartScene(windowSize);
	EndGameScene * endGame = new EndGameScene(windowSize);
	CreditsScene * creditsScene = new CreditsScene(windowSize);
	OptionsScene * optionsScene = new OptionsScene(windowSize);
	LevelSelectScene * lvlSelectScene = new LevelSelectScene(windowSize);

	//add scenes to sceneMgr
	SceneManager::getInstance()->addScene(gameScene);
	SceneManager::getInstance()->addScene(startScene);
	SceneManager::getInstance()->addScene(endGame);
	SceneManager::getInstance()->addScene(creditsScene);
	SceneManager::getInstance()->addScene(optionsScene);
	SceneManager::getInstance()->addScene(lvlSelectScene);

	//switch to splash
	SceneManager::getInstance()->switchTo(Scenes::SPLASH);
}

void Game::init()
{
	//InputManager::GetInstance()->RegisterEventCallback(EventListener::KeyboardEvent::MOUSE_WHEEL_UP, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, -1)), this);
	//InputManager::GetInstance()->RegisterEventCallback(EventListener::KeyboardEvent::MOUSE_WHEEL_DOWN, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, 1)), this);

	m_cameraManager.SetLevelSize(LevelLoader::loadLevel(LEVELS::PROTOTYPE));
	//m_camera.zoom(-1);
	initGameCamera = false;

	SceneManager::getInstance()->init(m_renderer);
}

void Game::loop(float dt)
{
	LevelLoader::destroyObjects();
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::GAME)
	{
		if (initGameCamera == false)
		{
			m_camera.zoom(-1);
			initGameCamera = true;
		}
		for (auto& system : m_systems)
		{
			system->process(dt);
		}
	}
	m_cameraManager.update(dt);
	SceneManager::getInstance()->update(dt);
	SceneManager::getInstance()->render(m_renderer);
}
