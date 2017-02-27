#include "stdafx.h" 
#include "CreditsScene.h"

CreditsScene::CreditsScene(Vector2D windowSize)
	: Scene(Scenes::CREDITS)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
{
	loadMedia();
}

void CreditsScene::update(float dt)
{
}

void CreditsScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	r.present();
}

bool CreditsScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&CreditsScene::changeScene, this, Scenes::SPLASH)), this, 0);

	return success;
}

void CreditsScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::CREDITS)
		SceneManager::getInstance()->switchTo(newScene);
}

bool CreditsScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("creditsscreen");

	return success;
}
