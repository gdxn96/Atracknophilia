#include "stdafx.h" 
#include "LobbyScene.h"

LobbyScene::LobbyScene(Vector2D windowSize)
	: Scene(Scenes::LOBBY)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(200)
	, m_rightBtnPos(800)
	, m_yBtnPos(350)
	, m_btnHeight(50)
	, m_btnWidth(250)
{
	m_hostBtn = Button();
	m_joinBtn = Button();
	m_highlightedBtn = Button();
	loadMedia();
}

void LobbyScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
}

void LobbyScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_hostBtn.render(r);
	m_joinBtn.render(r);
	m_highlightedBtn.render(r);
	r.present();
}

bool LobbyScene::init(Renderer & r)
{
	// init success flag
	bool success = true;
	
	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&LobbyScene::changeScene, this, Scenes::SPLASH)), this, 0);

	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LobbyScene::moveHighlightBtn, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LobbyScene::moveHighlightBtn, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&LobbyScene::executeScene, this)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LobbyScene::executeScene, this)), this, m_playerOneID);
	return success;
}

void LobbyScene::enter()
{
	m_hostBtn.setRect(Rect{ m_leftBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
	m_joinBtn.setRect(Rect{ m_rightBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_yBtnPos, m_btnWidth, m_btnHeight });

	m_hostBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("hostbtn"));
	m_joinBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("joinbtn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(left);
}

void LobbyScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::LOBBY)
	{
		currentTick = 0;
		SceneManager::getInstance()->switchTo(newScene);
	}
		
}

bool LobbyScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("lobbyselect");

	return success;
}

void LobbyScene::moveHighlightBtn(direction dir, IDs id)
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

void LobbyScene::executeScene()
{
	if (currentTick > 1)
	{
		if (m_hostBtn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::CHOOSEPLAYER);
		}
		if (m_joinBtn.getRect() == m_highlightedBtn.getRect())
		{
			changeScene(Scenes::ROOMSCENE);
		}
	}
}