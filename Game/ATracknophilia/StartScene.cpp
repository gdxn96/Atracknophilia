#include "stdafx.h" 
#include "StartScene.h"

StartScene::StartScene(Vector2D windowSize) 
	: Scene(Scenes::SPLASH)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
{
	m_startBtn = Button();
	loadMedia();
}

void StartScene::update(float dt)
{

}

void StartScene::render(Renderer& r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	r.present();
}

bool StartScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	//InputManager::GetInstance()->AddKey(EventListener::Event::BUTTON_START, new PressCommand(std::bind(&StartScene::changeScene, this, Scenes::GAME)));

	return success;
}

void StartScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::SPLASH)
		SceneManager::getInstance()->switchTo(newScene);
}

bool StartScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("startscreen");

	m_startBtn.setRect(Rect{ 0,0,100,100 });

	return success;
}