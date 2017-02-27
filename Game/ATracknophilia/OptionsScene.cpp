#include "stdafx.h" 
#include "OptionsScene.h"

OptionsScene::OptionsScene(Vector2D windowSize)
	: Scene(Scenes::OPTIONS)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
{
	loadMedia();
}

void OptionsScene::update(float dt)
{
}

void OptionsScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	r.present();
}

bool OptionsScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&OptionsScene::changeScene, this, Scenes::SPLASH)), this, 0);

	return success;
}

void OptionsScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::OPTIONS)
		SceneManager::getInstance()->switchTo(newScene);
}

bool OptionsScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("optionsscreen");

	return success;
}
