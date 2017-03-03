#include "stdafx.h"
#include "RoomScene.h"


RoomScene::RoomScene(Vector2D windowSize)
	: Scene(Scenes::ROOMSCENE)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(200)
	, m_rightBtnPos(800)
	, m_upBtnPos(250)
	, m_downBtnPos(500)
	, m_btnHeight(50)
	, m_btnWidth(250)
{
	m_room1Btn = Button();
	m_room2Btn = Button();
	m_room3Btn = Button();
	m_room4Btn = Button();
	m_highlightedBtn = Button();
	loadMedia();
}

void RoomScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
}

void RoomScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_room1Btn.render(r);
	m_room2Btn.render(r);
	m_room3Btn.render(r);
	m_room4Btn.render(r);
	m_highlightedBtn.render(r);
	r.present();
}

bool RoomScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&RoomScene::changeScene, this, Scenes::SPLASH)), this, 0);

	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&RoomScene::moveHighlightBtn, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&RoomScene::moveHighlightBtn, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_UP, new PressCommand(std::bind(&RoomScene::moveHighlightBtn, this, up, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&RoomScene::moveHighlightBtn, this, down, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&RoomScene::executeScene, this)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&RoomScene::executeScene, this)), this, m_playerOneID);
	return success;
}

void RoomScene::enter()
{
	m_room1Btn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_room2Btn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_room3Btn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_room4Btn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });

	m_room1Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("room1btn"));
	m_room2Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("room2btn"));
	m_room3Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("room3btn"));
	m_room4Btn.setTexture(ResourceManager::getInstance()->getTextureByKey("room4btn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(left);
}

void RoomScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::ROOMSCENE)
	{
		currentTick = 0;
		SceneManager::getInstance()->switchTo(newScene);
	}

}

bool RoomScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("lobbyselect");

	return success;
}

void RoomScene::moveHighlightBtn(direction dir, IDs id)
{
	if (id == m_playerOneID)
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
}

void RoomScene::executeScene()
{
	if (currentTick > 1)
	{
		if (m_room1Btn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::CHOOSEPLAYER);
		}
		if (m_room2Btn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::CHOOSEPLAYER);
		}
		if (m_room3Btn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::CHOOSEPLAYER);
		}
		if (m_room4Btn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::CHOOSEPLAYER);
		}
	}
}