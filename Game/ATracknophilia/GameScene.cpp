#include "stdafx.h" 
#include "GameScene.h"
#include "LevelLoader.h"
#include "EntityFactory.h"

GameScene::GameScene(int mapLvl)
	:	Scene(Scenes::GAME)
{
	if (mapLvl == 1)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::PROTOTYPE, "./assets/levels/map1.json" },
		});
	}
	if (mapLvl == 2)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::PROTOTYPE, "./assets/levels/map2.json" },
		});
	}
	if (mapLvl == 3)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::PROTOTYPE, "./assets/levels/map3.json" },
		});
	}
	if (mapLvl == 4)
	{
		LevelLoader::RegisterLevels({ //edit enum in LevelLoader.h
			{ LEVELS::PROTOTYPE, "./assets/levels/map4.json" },
		});
	}
}

void GameScene::destroy()
{
	// delete entities here..
}

void GameScene::enter()
{
	// if a way to switch levels is wanted do that here

	// take level enum to load particular level
}

bool GameScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	//InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_Y, new ReleaseCommand(std::bind(&GameScene::changeScene, this, Scenes::ENDGAME)), this);

	LevelLoader::loadLevel(LEVELS::PROTOTYPE);

	EntityFactory::SpawnPlayer(50, 12, 1, 1, 0);
	EntityFactory::SpawnPlayer(51, 12, 1, 1, 1);
	EntityFactory::SpawnBoostPad(12, 12, 3, 1);

	return success;
}

void GameScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::GAME)
		SceneManager::getInstance()->switchTo(newScene);
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