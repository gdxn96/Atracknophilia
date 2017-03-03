#include "stdafx.h" 
#include "OptionsScene.h"

OptionsScene::OptionsScene(Vector2D windowSize)
	: Scene(Scenes::OPTIONS)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(200)
	, m_rightBtnPos(800)
	, m_yBtnPos(350)
	, m_btnHeight(50)
	, m_btnWidth(250)
{
	m_onBtn = Button();
	m_offBtn = Button();
	m_highlightedBtn = Button();
	m_displayBtn = Button();
	m_selectedBtn = Button();
	loadMedia();
}

void OptionsScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
}

void OptionsScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_onBtn.render(r);
	m_offBtn.render(r);
	m_displayBtn.render(r);
	m_selectedBtn.render(r);
	m_highlightedBtn.render(r);
	r.present();
}

bool OptionsScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	m_onBtn.setRect(Rect{ m_leftBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
	m_offBtn.setRect(Rect{ m_rightBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
	m_displayBtn.setRect(Rect{ m_rightBtnPos - 350, m_yBtnPos +100, 350, 70 });
	m_selectedBtn.setRect(Rect{ m_rightBtnPos, m_yBtnPos +110, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });

	m_onBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("onbtn"));
	m_offBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("offbtn"));
	m_displayBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("soundeffectsbtn"));
	m_selectedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("onbtn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&OptionsScene::changeScene, this, Scenes::SPLASH)), this, 0);
	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&OptionsScene::moveHighlightBtn, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&OptionsScene::moveHighlightBtn, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&OptionsScene::executeScene, this)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&OptionsScene::executeScene, this)), this, m_playerOneID);

	return success;
}

void OptionsScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::OPTIONS)
	{
		currentTick = 0;
		SceneManager::getInstance()->switchTo(newScene);
	}
	
}

bool OptionsScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("optionsscreen");

	return success;
}

void OptionsScene::moveHighlightBtn(direction dir, IDs id)
{
	if (id == m_playerOneID)
	{
		if (dir == left && m_highlightedBtn.getDirection() != left)
		{
			m_highlightedBtn.setDirection(left);
			m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
		}
		if (dir == right && m_highlightedBtn.getDirection() != right)
		{
			m_highlightedBtn.setDirection(right);
			m_highlightedBtn.setRect(Rect{ m_rightBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
		}
	}
}

void OptionsScene::executeScene()
{
	if (currentTick > 1)
	{
		if (m_onBtn.getRect() == m_highlightedBtn.getRect())
		{
			m_selectedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("onbtn"));
			//changeScene(Scenes::CHOOSEPLAYER);
		}
		if (m_offBtn.getRect() == m_highlightedBtn.getRect())
		{
			m_selectedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("offbtn"));
			//changeScene(Scenes::ROOMSCENE);
		}
	}
}
