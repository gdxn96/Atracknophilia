#include "stdafx.h" 
#include "GameScene.h"
#include "LevelLoader.h"
#include "EntityFactory.h"

GameScene::GameScene()
	:	Scene(Scenes::GAME)
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
}

bool GameScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	//InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_Y, new ReleaseCommand(std::bind(&GameScene::changeScene, this, Scenes::ENDGAME)), this);


	// Add this to on entry()

	m_cameraManager = CameraManager();
	m_cameraManager.SetLevelSize(m_currentLvl);

	for (int i = 0; i < m_playerIds.size(); i++)
	{
		if (i != 15) // a value I have given to a player slot when there is no controller 
		{
			EntityFactory::SpawnPlayer(50 + i, 12, 1, 1, i);
		}
	}

	//EntityFactory::SpawnPlayer(50, 12, 1, 1, 0);
	//EntityFactory::SpawnPlayer(51, 12, 1, 1, 1);
	EntityFactory::SpawnBoostPad(12, 12, 3, 1);

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

void GameScene::update(float dt)
{
	/*for (auto& system : m_systems)
	{
		system->process(dt);
	}*/
	m_cameraManager.update(dt);
}

void GameScene::render(Renderer & r)
{
	// not needing on this scene as the render system draws and this gets done in render system update
}