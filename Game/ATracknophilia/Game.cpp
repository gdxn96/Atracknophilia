#include "stdafx.h"
#include "Game.h"
#include "FLInput\FLInputManager.h"
#include "LevelLoader.h"
#include "EntityFactory.h"
#include "DirectionVolume.h"

bool Game::quit = false;

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) 
	:	m_resourceMgr(ResourceManager::getInstance())
{
	m_net.setMessageCallback([this](Message m) { this->notifyMessage(m); });
	LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
		{ LEVELS::LEVEL1, "./assets/levels/map1.json" },
		{ LEVELS::LEVEL2, "./assets/levels/map2.json" },
		{ LEVELS::LEVEL3, "./assets/levels/map3.json" },
		{ LEVELS::LEVEL4, "./assets/levels/map4.json" }
	});

	m_renderer.init(windowSize, windowName, &m_camera);
	m_camera.init(windowSize.w, windowSize.h, m_renderer.getRenderer());


	//Declare systems
	auto inputSys = new InputSystem();
	auto renderSys = new RenderSystem();
	auto collisionSystem = new CollisionSystem();
	auto physicsSystem = new PhysicsSystem();
	auto aiSystem = new AISystem();
	auto hookSys = new HookSystem();
	auto powerUpSys = new PowerUpSystem();
	auto swapSys = new SwapSystem();

	//Init systems
	renderSys->init(&m_renderer);

	//Push back systems
	m_systems.push_back(inputSys);
	m_systems.push_back(collisionSystem);
	m_systems.push_back(inputSys);
	m_systems.push_back(hookSys);
	m_systems.push_back(powerUpSys);
	m_systems.push_back(swapSys);
	m_systems.push_back(physicsSystem);
	m_systems.push_back(aiSystem);

	m_cameraManager = CameraManager();
	m_cameraManager.init(&m_camera);

	//render system must be added last
	m_systems.push_back(renderSys);

	m_resourceMgr->init(&m_renderer);
	m_resourceMgr->loadResources(".//assets//resources.json");
	m_resourceMgr->loadResourceQueue();

	//create scenes

	StartScene * startScene = new StartScene(windowSize);
	EndGameScene * endGame = new EndGameScene(windowSize);
	CreditsScene * creditsScene = new CreditsScene(windowSize);
	OptionsScene * optionsScene = new OptionsScene(windowSize);
	GameScene * gameScene = new GameScene(&m_cameraManager);
	LevelSelectScene * lvlSelectScene = new LevelSelectScene(windowSize);
	lvlSelectScene->m_gameScene = gameScene;
	ChoosePlayerScene * choosePlayerScene = new ChoosePlayerScene(windowSize);
	choosePlayerScene->m_lvl = lvlSelectScene;
	LobbyScene * lobbyScene = new LobbyScene(windowSize);
	RoomScene * roomScene = new RoomScene(windowSize);

	//add scenes to sceneMgr
	SceneManager::getInstance()->addScene(startScene);
	SceneManager::getInstance()->addScene(endGame);
	SceneManager::getInstance()->addScene(creditsScene);
	SceneManager::getInstance()->addScene(optionsScene);
	SceneManager::getInstance()->addScene(gameScene);
	SceneManager::getInstance()->addScene(lvlSelectScene);
	SceneManager::getInstance()->addScene(choosePlayerScene);
	SceneManager::getInstance()->addScene(lobbyScene);
	SceneManager::getInstance()->addScene(roomScene);

	//switch to splash
	SceneManager::getInstance()->switchTo(Scenes::SPLASH);
}

void Game::init()
{
	m_camera.setZoomProps(Camera2D::DEFAULT_ZOOM_SPEED, Camera2D::DEFAULT_ZOOMTO_SPEED, 1.f, 0.1f);
	m_camera.zoomToFit({
		Camera2D::Point(0, 0),
		Camera2D::Point(1280, 720)
	});
	m_camera.setCentre(Camera2D::Point(640, 360));

	InputManager::GetInstance()->RegisterEventCallback(EventListener::KeyboardEvent::MOUSE_WHEEL_UP, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, -1)), this);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::KeyboardEvent::MOUSE_WHEEL_DOWN, new PressCommand(std::bind(&Camera2D::Camera::zoom, &m_camera, 1)), this);

	SceneManager::getInstance()->init(m_renderer);
}

void Game::loop(float dt)
{
	LevelLoader::destroyObjects();
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::GAME)
	{
		for (auto& system : m_systems)
		{
			system->process(dt);
		}
	}
	m_cameraManager.update(dt);

	SceneManager::getInstance()->update(dt);
	SceneManager::getInstance()->render(m_renderer);

	sendData(); //periodically send data, tick system should exist
	try
	{
		m_net.update();
	}
	catch (...)
	{
		//dont crash if servers down
	}
}

void Game::notifyMessage(Message m)
{
	std::cout << m.data << std::endl;
}

void Game::sendData()
{
	bool m_host = rand() % 2; //decided by player in lobby menues

	if (m_host)
	{
		//m_net.sendToAll(Message("", "yayyy"));
	}
	else
	{
		//m_net.sendToHost(Message("", "yayyy"));
	}
}
