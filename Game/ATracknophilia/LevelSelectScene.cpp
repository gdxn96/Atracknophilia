#include "stdafx.h" 
#include "LevelSelectScene.h"

LevelSelectScene::LevelSelectScene(Vector2D windowSize)
	: Scene(Scenes::LEVELSELECT)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(50)
	, m_rightBtnPos(500)
	, m_upBtnPos(50)
	, m_downBtnPos(400)
	, m_btnHeight(250)
	, m_btnWidth(250)
{
	m_lvl1Btn = Button();
	m_lvl2Btn = Button();
	m_lvl3Btn = Button();
	m_lvl4Btn = Button();
	m_highlightedBtn = Button();
	m_tickABtn = Button();
	m_tickBBtn = Button();
	m_tickCBtn = Button();
	m_tickDBtn = Button();
	loadMedia();
}

void LevelSelectScene::update(float dt)
{
}

void LevelSelectScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_lvl1Btn.render(r);
	m_lvl2Btn.render(r);
	m_lvl3Btn.render(r);
	m_lvl4Btn.render(r);
	m_highlightedBtn.render(r);
	m_tickABtn.render(r);
	m_tickBBtn.render(r);
	m_tickCBtn.render(r);
	m_tickDBtn.render(r);
	r.present();
}

bool LevelSelectScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	m_lvl1Btn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_lvl2Btn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_lvl3Btn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_lvl4Btn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });

	m_lvl1Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("lvl1btn"));
	m_lvl2Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("lvl2btn"));
	m_lvl3Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("lvl3btn"));
	m_lvl4Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("lvl4btn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_tickABtn.setTexture(ResourceManager::getInstance()->getTextureByKey("tickbtn"));
	m_tickBBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("tickbtn"));
	m_tickCBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("tickbtn"));
	m_tickDBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("tickbtn"));

	m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LevelSelectScene::moveHighlightBtn, this, left)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LevelSelectScene::moveHighlightBtn, this, right)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_UP, new PressCommand(std::bind(&LevelSelectScene::moveHighlightBtn, this, up)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&LevelSelectScene::moveHighlightBtn, this, down)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&LevelSelectScene::changeScene, this, Scenes::SPLASH)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LevelSelectScene::executeScene, this)), this, 0);

	return success;
}

void LevelSelectScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::LEVELSELECT)
		SceneManager::getInstance()->switchTo(newScene);
}

bool LevelSelectScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("lobbyselect");

	return success;
}

void LevelSelectScene::moveHighlightBtn(direction dir)
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

void LevelSelectScene::executeScene()
{
	if (m_lvl1Btn.getRect() == m_highlightedBtn.getRect())
	{
		// load lvl 1 here
	}
	if (m_lvl2Btn.getRect() == m_highlightedBtn.getRect())
	{
		// load lvl 2 here
	}
	if (m_lvl3Btn.getRect() == m_highlightedBtn.getRect())
	{
		// load lvl 3 here
	}
	if (m_lvl4Btn.getRect() == m_highlightedBtn.getRect())
	{
		// load lvl 4 here
	}
}