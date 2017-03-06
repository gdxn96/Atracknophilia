#include "stdafx.h" 
#include "GameScene.h"
#include "LevelLoader.h"
#include "EntityFactory.h"

GameScene::GameScene(CameraManager  *cameraManager)
	: Scene(Scenes::GAME)
	, m_cameraManager(cameraManager)
{

}

void GameScene::destroy()
{
	// delete entities here..
}

void GameScene::enter()
{
	// if a way to switch levels is wanted do that here

	// take level enum to load particular level

	if (m_mapLvl == 1)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::LEVEL1, "./assets/levels/map1.json" },
		});
		LevelLoader::loadLevel(LEVELS::LEVEL1);
		m_currentLvl = LevelLoader::loadLevel(LEVELS::LEVEL1);
	}
	if (m_mapLvl == 2)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::LEVEL2, "./assets/levels/map2.json" },
		});
		LevelLoader::loadLevel(LEVELS::LEVEL2);
		m_currentLvl = LevelLoader::loadLevel(LEVELS::LEVEL2);
	}
	if (m_mapLvl == 3)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::LEVEL3, "./assets/levels/map3.json" },
		});
		LevelLoader::loadLevel(LEVELS::LEVEL3);
		m_currentLvl = LevelLoader::loadLevel(LEVELS::LEVEL3);
	}
	if (m_mapLvl == 4)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::LEVEL4, "./assets/levels/map4.json" },
		});
		LevelLoader::loadLevel(LEVELS::LEVEL4);
		m_currentLvl = LevelLoader::loadLevel(LEVELS::LEVEL4);
	}

	// Add this to on entry()


	m_cameraManager->SetLevelSize(m_currentLvl);

	for (int i = 0; i < m_playerIds.size(); i++)
	{
		if (i != 15) // a value I have given to a player slot when there is no controller 
		{
			EntityFactory::SpawnPlayer(50 + i, 12, 1, 1, i);
		}
	}
	if (m_aiEnabled)
	{
		for (int j= 0; j< 4 - m_playerIds.size(); j++)
		{
			EntityFactory::SpawnPlayer(51 + j, 12, 1, 1, 0, true);
		}
	}

	auto cam = m_cameraManager->getCamera();
	float zoomSpeed = 0.01f; //speed the camera zooms in or out (smaller due to no deltaTime)
	float zoomToSpeed = 1000.f; //when using zoom to (no deltaTime)
	float minZoom = 0.15f; //minimum level of zoom
	float maxZoom = 0.08f; //maximum threshold you can zoom in until;
	cam->setZoomProps(zoomSpeed, zoomToSpeed, minZoom, maxZoom);
}

void GameScene::exit()
{
	auto cam = m_cameraManager->getCamera();
	cam->setZoomProps(Camera2D::DEFAULT_ZOOM_SPEED, Camera2D::DEFAULT_ZOOMTO_SPEED, 1.f, 0.1f);
	cam->zoomToFit({
		Camera2D::Point(0, 0),
		Camera2D::Point(1280, 720)
	});
	cam->setCentre(Camera2D::Point(640, 360));
}

bool GameScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	return success;
}

void GameScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::GAME)
		SceneManager::getInstance()->switchTo(newScene);
}

void GameScene::initialiseMapLvls(int mapLvl)
{
	m_mapLvl = mapLvl;
}

void GameScene::initialiseGameScenePlayerIDs(vector<int> playerIDs)
{
	m_playerIds = playerIDs;
}

void GameScene::initAiEnabled(bool aiEnabled)
{
	m_aiEnabled = aiEnabled;
}

void GameScene::update(float dt)
{
	/*for (auto& system : m_systems)
	{
	system->process(dt);
	}*/
}

void GameScene::render(Renderer & r)
{
	// not needing on this scene as the render system draws and this gets done in render system update
}