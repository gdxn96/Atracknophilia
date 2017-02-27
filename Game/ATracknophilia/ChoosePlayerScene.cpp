#include "stdafx.h" 
#include "ChoosePlayerScene.h"

ChoosePlayerScene::ChoosePlayerScene(Vector2D windowSize)
	: Scene(Scenes::CHOOSEPLAYER)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(50)
	, m_rightBtnPos(400)
	, m_upBtnPos(150)
	, m_downBtnPos(500)
	, m_btnHeight(189)
	, m_btnWidth(250)
{
	m_playerABtn = Button();
	m_playerBBtn = Button();
	m_playerCBtn = Button();
	m_playerDBtn = Button();
	m_highlightedBtn = Button();
	loadMedia();
}

void ChoosePlayerScene::update(float dt)
{
}

void ChoosePlayerScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_playerABtn.render(r);
	m_playerBBtn.render(r);
	m_playerCBtn.render(r);
	m_playerDBtn.render(r);
	m_highlightedBtn.render(r);
	r.present();
}

bool ChoosePlayerScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	m_playerABtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerBBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerCBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_playerDBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });

	m_playerABtn.setTexture(ResourceManager::getInstance()->getTextureByKey("playerAbtn"));
	m_playerBBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("playerBbtn"));
	m_playerCBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("playerCbtn"));
	m_playerDBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("playerDbtn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightBtn, this, left)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightBtn, this, right)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_UP, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightBtn, this, up)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightBtn, this, down)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&ChoosePlayerScene::changeScene, this, Scenes::SPLASH)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this)), this, 0);

	return success;
}

void ChoosePlayerScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::CHOOSEPLAYER)
		SceneManager::getInstance()->switchTo(newScene);
}

bool ChoosePlayerScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("levelselect");

	return success;
}

void ChoosePlayerScene::moveHighlightBtn(direction dir)
{
	if (dir == left && m_highlightedBtn.getDirection() != left)
	{
		m_highlightedBtn.setDirection(left);
		if (m_highlightedBtn.getRect().pos.y == m_upBtnPos)
		{
			m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
		}
		else
			m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	}
	if (dir == right && m_highlightedBtn.getDirection() != right)
	{
		m_highlightedBtn.setDirection(right);
		if (m_highlightedBtn.getRect().pos.y == m_upBtnPos)
		{
			m_highlightedBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
		}
		else
			m_highlightedBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	}
	if (dir == up && m_highlightedBtn.getDirection() != up)
	{
		m_highlightedBtn.setDirection(up);
		if (m_highlightedBtn.getRect().pos.x == m_rightBtnPos)
		{
			m_highlightedBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
		}
		else
			m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	}
	if (dir == down && m_highlightedBtn.getDirection() != down)
	{
		m_highlightedBtn.setDirection(down);
		if (m_highlightedBtn.getRect().pos.x == m_rightBtnPos)
		{
			m_highlightedBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
		}
		else
			m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	}
}

void ChoosePlayerScene::executeScene()
{
	if (m_playerABtn.getRect() == m_highlightedBtn.getRect())
	{
		// load pA here
	}
	if (m_playerBBtn.getRect() == m_highlightedBtn.getRect())
	{
		// load pB here
	}
	if (m_playerCBtn.getRect() == m_highlightedBtn.getRect())
	{
		// load pC here
	}
	if (m_playerDBtn.getRect() == m_highlightedBtn.getRect())
	{
		// load pD here
	}
}