#include "stdafx.h" 
#include "EndGameScene.h"

EndGameScene::EndGameScene(Vector2D windowSize) 
	: Scene(Scenes::ENDGAME)
	, m_windowSize(windowSize)
{
	loadMedia();
}

void EndGameScene::update(float dt)
{
	currentTick++;
}

void EndGameScene::render(Renderer& r)
{
	SDL_RenderClear(r.getRenderer());
	r.present();
}

bool EndGameScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	//InputManager::GetInstance()->AddKey(EventListener::Event::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&EndGameScene::changeScene, this, Scenes::SPLASH)));
	//InputManager::GetInstance()->AddKey(EventListener::Event::BUTTON_BACK, new PressCommand(std::bind(&EndGameScene::changeScene, this, Scenes::GAME)));

	return success;
}

void EndGameScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::ENDGAME)
		SceneManager::getInstance()->switchTo(newScene);
}

bool EndGameScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load endgame image here ...
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("gameover");

	return success;
}