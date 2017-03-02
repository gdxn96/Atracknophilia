#include "stdafx.h" 
#include "ChoosePlayerScene.h"

ChoosePlayerScene::ChoosePlayerScene(Vector2D windowSize)
	: Scene(Scenes::CHOOSEPLAYER)
	, m_windowSize(windowSize)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(100)
	, m_rightBtnPos(500)
	, m_upBtnPos(150)
	, m_downBtnPos(500)
	, m_btnHeight(189)
	, m_btnWidth(250)
	, m_aiXPos(1000)
	, m_aiYPos(300)
	, m_aiHeight(50)
{
	m_playerABtn = Button();
	m_playerBBtn = Button();
	m_playerCBtn = Button();
	m_playerDBtn = Button();
	m_aLeftArrowBtn = Button();
	m_aRightArrowBtn = Button();
	m_bLeftArrowBtn = Button();
	m_bRightArrowBtn = Button();
	m_cLeftArrowBtn = Button();
	m_cRightArrowBtn = Button();
	m_dLeftArrowBtn = Button();
	m_dRightArrowBtn = Button();
	m_highlightedBtn = Button();
	m_aiEnabled = Button();
	m_aiDisabled = Button();
	m_aiChoice = Button();
	loadMedia();
}

void ChoosePlayerScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
	checkForControllers();
	if (lockedA && lockedB && lockedC && lockedD)
		changeScene(Scenes::LEVELSELECT);
}

void ChoosePlayerScene::render(Renderer & r)
{
	if (renderInit == false) { m_r = r; renderInit = true; }
	r.drawTexture(m_splashScreen, m_textureRect);
	m_playerABtn.render(r);
	m_playerBBtn.render(r);
	m_playerCBtn.render(r);
	m_playerDBtn.render(r);
	m_aLeftArrowBtn.render(r);
	m_aRightArrowBtn.render(r);
	m_bLeftArrowBtn.render(r);
	m_bRightArrowBtn.render(r);
	m_cLeftArrowBtn.render(r);
	m_cRightArrowBtn.render(r);
	m_dLeftArrowBtn.render(r);
	m_dRightArrowBtn.render(r);
	m_highlightedBtn.render(r);
	m_aiEnabled.render(r);
	m_aiDisabled.render(r);
	m_aiChoice.render(r);
	r.present();
}

void ChoosePlayerScene::enter()
{
	// initialise the change-able variables upon scene entry, so they will reset when scene is left and entered again
	currentTick = 0;
	renderInit = false;
	lockedA = false;
	lockedB = false;
	lockedC = false;
	lockedD = false;
	m_isAiEnabled = false;
	m_blueID = 0;
	m_greenID = 1;
	m_redID = 2;
	m_yellowID = 3;
	m_lockedInID = 99;
	m_arrowHeight = 15;
	m_arrowWidth = 30;
	m_scaler = 1.5;

	m_playerABtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerBBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerCBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_playerDBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_aiXPos, m_aiYPos, m_btnWidth, m_aiHeight });
	m_aiEnabled.setRect(Rect{ m_aiXPos, m_aiYPos, m_btnWidth, m_aiHeight });
	m_aiDisabled.setRect(Rect{ m_aiXPos, m_aiYPos * m_scaler, m_btnWidth, m_aiHeight });
	m_aiChoice.setRect(Rect{ m_aiXPos, m_aiYPos * 2, m_btnWidth, m_aiHeight });

	m_aLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_aRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_bLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_bRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_cLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_cRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_dLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_dRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });

	m_blueTex = ResourceManager::getInstance()->getTextureByKey("playerAbtn");
	m_greenTex = ResourceManager::getInstance()->getTextureByKey("playerBbtn");
	m_redTex = ResourceManager::getInstance()->getTextureByKey("playerCbtn");
	m_yellowTex = ResourceManager::getInstance()->getTextureByKey("playerDbtn");

	m_leftArrowTex = ResourceManager::getInstance()->getTextureByKey("arrowleftbtn");
	m_rightArrowTex = ResourceManager::getInstance()->getTextureByKey("arrowrightbtn");

	m_noControllerTex = ResourceManager::getInstance()->getTextureByKey("nocontroller");

	m_aiTex = ResourceManager::getInstance()->getTextureByKey("disabledText");

	m_playerABtn.setTexture(m_blueTex);
	m_playerBBtn.setTexture(m_greenTex);
	m_playerCBtn.setTexture(m_redTex);
	m_playerDBtn.setTexture(m_yellowTex);

	m_aLeftArrowBtn.setTexture(m_leftArrowTex);
	m_aRightArrowBtn.setTexture(m_rightArrowTex);
	m_bLeftArrowBtn.setTexture(m_leftArrowTex);
	m_bRightArrowBtn.setTexture(m_rightArrowTex);
	m_cLeftArrowBtn.setTexture(m_leftArrowTex);
	m_cRightArrowBtn.setTexture(m_rightArrowTex);
	m_dLeftArrowBtn.setTexture(m_leftArrowTex);
	m_dRightArrowBtn.setTexture(m_rightArrowTex);

	m_aiEnabled.setTexture(ResourceManager::getInstance()->getTextureByKey("enableAiBtn"));
	m_aiDisabled.setTexture(ResourceManager::getInstance()->getTextureByKey("disableAiBtn"));
	m_aiChoice.setTexture(m_aiTex);

	m_playerABtn.m_playerID = m_playerOneID;
	m_playerBBtn.m_playerID = m_playerTwoID;
	m_playerCBtn.m_playerID = m_playerThreeID;
	m_playerDBtn.m_playerID = m_playerFourID;

	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(up);
}

bool ChoosePlayerScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&ChoosePlayerScene::changeScene, this, Scenes::SPLASH)), this, m_playerOneID);
	
	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_UP, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightedBtn, this, up)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&ChoosePlayerScene::moveHighlightedBtn, this, down)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_Y, new PressCommand(std::bind(&ChoosePlayerScene::updateAiChoice, this)), this, m_playerOneID);

	// player2
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerTwoID)), this, m_playerTwoID);

	// player3
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerThreeID)), this, m_playerThreeID);

	// player4
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&ChoosePlayerScene::reduceArrowScale, this, right, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerFourID)), this, m_playerFourID);

	return success;
}

void ChoosePlayerScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::CHOOSEPLAYER)
	{
		currentTick = 0;
		SceneManager::getInstance()->switchTo(newScene);
	}	
}

bool ChoosePlayerScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("lobbyselect");

	return success;
}

void ChoosePlayerScene::changePlayerColour(direction dir, int controllerId)
{
	switch (controllerId)
	{
	case m_playerOneID:
		if (lockedA == false) { changeCharacter(dir, m_playerOneID); }
		updatePlayer(m_playerABtn.m_playerID, m_playerOneID);
		break;
	case m_playerTwoID:
		if (lockedB == false) { changeCharacter(dir, m_playerTwoID); }
		updatePlayer(m_playerBBtn.m_playerID, m_playerTwoID);
		break;
	case m_playerThreeID:
		if (lockedC == false) { changeCharacter(dir, m_playerThreeID); }
		updatePlayer(m_playerCBtn.m_playerID, m_playerThreeID);
		break;
	case m_playerFourID:
		if (lockedD == false) { changeCharacter(dir, m_playerFourID); }
		updatePlayer(m_playerDBtn.m_playerID, m_playerFourID);
		break;
	}
}

void ChoosePlayerScene::moveHighlightedBtn(direction dir)
{
	if (currentTick > 1)
	{
		if (dir == up && m_highlightedBtn.getDirection() != up)
		{
			m_highlightedBtn.setDirection(up);
			m_highlightedBtn.setRect(Rect{ m_aiXPos, m_aiYPos, m_btnWidth, m_aiHeight });
		}
		if (dir == down && m_highlightedBtn.getDirection() != down)
		{
			m_highlightedBtn.setDirection(down);
			m_highlightedBtn.setRect(Rect{ m_aiXPos, m_aiYPos * m_scaler, m_btnWidth, m_aiHeight });
		}
	}
}

void ChoosePlayerScene::reduceArrowScale(direction dir, int controllerID)
{
	if (currentTick > 1)
	{
		if (controllerID == m_playerOneID)
		{
			if (dir == left)
			{
				m_aLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
				
			}
			if (dir == right)
			{
				m_aRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
			}
		}
		if (controllerID == m_playerTwoID)
		{
			if (dir == left)
			{
				m_bLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
				
			}
			if (dir == right)
			{
				m_bRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
			}
		}
		if (controllerID == m_playerThreeID)
		{
			if (dir == left)
			{
				m_cLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
				
			}
			if (dir == right)
			{
				m_cRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
			}
		}
		if (controllerID == m_playerFourID)
		{
			if (dir == left)
			{
				m_dLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
				
			}
			if (dir == right)
			{
				m_dRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
			}
		}
	}
}

void ChoosePlayerScene::changeCharacter(direction dir, IDs id)
{
	if (currentTick > 1)
	{
		if (id == m_playerOneID)
		{
			if (dir == left)
			{
				m_aLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerABtn.m_playerID--;
				if (m_playerABtn.m_playerID < 0)
				{
					m_playerABtn.m_playerID = 3;
				}
			}
			if (dir == right)
			{
				m_aRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerABtn.m_playerID++;
				if (m_playerABtn.m_playerID > 3)
				{
					m_playerABtn.m_playerID = 0;
				}
			}
		}
		if (id == m_playerTwoID)
		{
			if (dir == left)
			{
				m_bLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerBBtn.m_playerID--;
				if (m_playerBBtn.m_playerID < 0)
				{
					m_playerBBtn.m_playerID = 3;
				}
			}
			if (dir == right)
			{
				m_bRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerBBtn.m_playerID++;
				if (m_playerBBtn.m_playerID > 3)
				{
					m_playerBBtn.m_playerID = 0;
				}
			}
		}
		if (id == m_playerThreeID)
		{
			if (dir == left)
			{
				m_cLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerCBtn.m_playerID--;
				if (m_playerCBtn.m_playerID < 0)
				{
					m_playerCBtn.m_playerID = 3;
				}
			}
			if (dir == right)
			{
				m_cRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerCBtn.m_playerID++;
				if (m_playerCBtn.m_playerID > 3)
				{
					m_playerCBtn.m_playerID = 0;
				}
			}
		}
		if (id == m_playerFourID)
		{
			if (dir == left)
			{
				m_dLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerDBtn.m_playerID--;
				if (m_playerDBtn.m_playerID < 0)
				{
					m_playerDBtn.m_playerID = 3;
				}
			}
			if (dir == right)
			{
				m_dRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth * m_scaler, m_arrowHeight * m_scaler });
				m_playerDBtn.m_playerID++;
				if (m_playerDBtn.m_playerID > 3)
				{
					m_playerDBtn.m_playerID = 0;
				}
			}
		}
	}
}

void ChoosePlayerScene::updatePlayer(int buttonID, IDs id)
{
	if (id == m_playerOneID && lockedA == false)
	{
		if (buttonID == 0) { m_playerABtn.setTexture(m_blueTex); }
		if (buttonID == 1) { m_playerABtn.setTexture(m_greenTex);}
		if (buttonID == 2) { m_playerABtn.setTexture(m_redTex);  }
		if (buttonID == 3) { m_playerABtn.setTexture(m_yellowTex);}
	}
	if (id == m_playerTwoID  && lockedB == false)
	{
		if (buttonID == 0) { m_playerBBtn.setTexture(m_blueTex); }
		if (buttonID == 1) { m_playerBBtn.setTexture(m_greenTex); }
		if (buttonID == 2) { m_playerBBtn.setTexture(m_redTex); }
		if (buttonID == 3) { m_playerBBtn.setTexture(m_yellowTex); }
	}
	if (id == m_playerThreeID  && lockedC == false)
	{
		if (buttonID == 0) { m_playerCBtn.setTexture(m_blueTex); }
		if (buttonID == 1) { m_playerCBtn.setTexture(m_greenTex); }
		if (buttonID == 2) { m_playerCBtn.setTexture(m_redTex); }
		if (buttonID == 3) { m_playerCBtn.setTexture(m_yellowTex); }
	}
	if (id == m_playerFourID  && lockedD == false)
	{
		if (buttonID == 0) { m_playerDBtn.setTexture(m_blueTex); }
		if (buttonID == 1) { m_playerDBtn.setTexture(m_greenTex); }
		if (buttonID == 2) { m_playerDBtn.setTexture(m_redTex); }
		if (buttonID == 3) { m_playerDBtn.setTexture(m_yellowTex); }
	}
}

void ChoosePlayerScene::checkIDs(int buttonID)
{
	if (m_playerABtn.m_playerID == buttonID)
	{
		if (m_blueID != m_lockedInID)
		{
			m_playerABtn.setTexture(m_blueTex);
		}
		else if (m_greenID != m_lockedInID)
		{
			m_playerABtn.setTexture(m_greenTex);
		}
		else if (m_redID != m_lockedInID)
		{
			m_playerABtn.setTexture(m_redTex);
		}
		else if (m_yellowID != m_lockedInID)
		{
			m_playerABtn.setTexture(m_yellowTex);
		}
	}
	if (m_playerBBtn.m_playerID == buttonID)
	{
		if (m_blueID != m_lockedInID)
		{
			m_playerBBtn.setTexture(m_blueTex);
		}
		else if (m_greenID != m_lockedInID)
		{
			m_playerBBtn.setTexture(m_greenTex);
		}
		else if (m_redID != m_lockedInID)
		{
			m_playerBBtn.setTexture(m_redTex);
		}
		else if (m_yellowID != m_lockedInID)
		{
			m_playerBBtn.setTexture(m_yellowTex);
		}
	}
	if (m_playerCBtn.m_playerID == buttonID)
	{
		if (m_blueID != m_lockedInID)
		{
			m_playerCBtn.setTexture(m_blueTex);
		}
		else if (m_greenID != m_lockedInID)
		{
			m_playerCBtn.setTexture(m_greenTex);
		}
		else if (m_redID != m_lockedInID)
		{
			m_playerCBtn.setTexture(m_redTex);
		}
		else if (m_yellowID != m_lockedInID)
		{
			m_playerCBtn.setTexture(m_yellowTex);
		}
	}
	if (m_playerDBtn.m_playerID == buttonID)
	{
		if (m_blueID != m_lockedInID)
		{
			m_playerDBtn.setTexture(m_blueTex);
		}
		else if (m_greenID != m_lockedInID)
		{
			m_playerDBtn.setTexture(m_greenTex);
		}
		else if (m_redID != m_lockedInID)
		{
			m_playerDBtn.setTexture(m_redTex);
		}
		else if (m_yellowID != m_lockedInID)
		{
			m_playerDBtn.setTexture(m_yellowTex);
		}
	}
}

void ChoosePlayerScene::checkForControllers()
{
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		m_playerABtn.setTexture(m_noControllerTex);
		m_playerBBtn.setTexture(m_noControllerTex);
		m_playerCBtn.setTexture(m_noControllerTex);
		m_playerDBtn.setTexture(m_noControllerTex);

		m_controllerTwoConnected = false;
		m_controllerThreeConnected = false;
		m_controllerFourConnected = false;
	}
	else if (SDL_NumJoysticks() < 2)
	{
		m_playerBBtn.setTexture(m_noControllerTex);
		m_playerCBtn.setTexture(m_noControllerTex);
		m_playerDBtn.setTexture(m_noControllerTex);

		playerIDs.push_back(15);

		m_controllerTwoConnected = false;
		m_controllerThreeConnected = false;
		m_controllerFourConnected = false;
	}
	else if (SDL_NumJoysticks() < 3)
	{
		m_playerCBtn.setTexture(m_noControllerTex);
		m_playerDBtn.setTexture(m_noControllerTex);

		playerIDs.push_back(15);

		m_controllerTwoConnected = true;
		m_controllerThreeConnected = false;
		m_controllerFourConnected = false;
	}
	else if (SDL_NumJoysticks() < 4)
	{
		m_playerDBtn.setTexture(m_noControllerTex);

		playerIDs.push_back(15);

		m_controllerTwoConnected = true;
		m_controllerThreeConnected = true;
		m_controllerFourConnected = false;
	}
	else if (SDL_NumJoysticks() < 5)
	{
		playerIDs.push_back(15);

		m_controllerTwoConnected = true;
		m_controllerThreeConnected = true;
		m_controllerFourConnected = true;
	}
}

void ChoosePlayerScene::updateAiChoice()
{
	if (currentTick > 1)
	{
		if (m_aiEnabled.getRect() == m_highlightedBtn.getRect())
		{
			m_aiTex = ResourceManager::getInstance()->getTextureByKey("enabledText");
			m_aiChoice.setTexture(m_aiTex);
			m_isAiEnabled = true;
		}
		if (m_aiDisabled.getRect() == m_highlightedBtn.getRect())
		{
			m_aiTex = ResourceManager::getInstance()->getTextureByKey("disabledText");
			m_aiChoice.setTexture(m_aiTex);
			m_isAiEnabled = false;
		}
	}
}

void ChoosePlayerScene::loadLevelSelect(Scenes scene, vector<int> playerIDs)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::CHOOSEPLAYER)
	{
		m_lvl->initialisePlayerIDS(playerIDs);
		SceneManager::getInstance()->switchTo(scene);
	}
}

void ChoosePlayerScene::executeScene(IDs id)
{
	if (currentTick > 1)
	{
		if (id == m_playerOneID && lockedA == false)
		{
			if (m_playerABtn.m_playerID == m_blueID)
			{
				m_blueTex = ResourceManager::getInstance()->getTextureByKey("greyedBlue");
				m_playerABtn.setTexture(m_blueTex);
				playerIDs.at(0) = m_blueID;
				m_blueID = m_lockedInID;
				m_playerABtn.m_playerID = 55;  // set player id to any number greater than 4 so it will never be available to select again
				checkIDs(0);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerABtn.setTexture(m_greenTex);
				playerIDs.at(0) = m_greenID;
				m_greenID = m_lockedInID;
				m_playerABtn.m_playerID = 55;
				checkIDs(1);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerABtn.setTexture(m_redTex);
				playerIDs.at(0) = m_redID;
				m_redID = m_lockedInID;
				m_playerABtn.m_playerID = 55;
				checkIDs(2);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerABtn.setTexture(m_yellowTex);
				playerIDs.at(0) = m_yellowID;
				m_yellowID = m_lockedInID;
				m_playerABtn.m_playerID = 55;
				checkIDs(3);
				lockedA = true;
			}	
		}

		if (id == m_playerTwoID && lockedB == false)
		{
			if (m_playerBBtn.m_playerID == m_blueID)
			{
				m_blueTex = ResourceManager::getInstance()->getTextureByKey("greyedBlue");
				m_playerBBtn.setTexture(m_blueTex);
				playerIDs.at(1) = m_blueID;
				m_playerBBtn.m_playerID = 55;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerBBtn.setTexture(m_greenTex);
				playerIDs.at(1) = m_greenID;
				m_playerBBtn.m_playerID = 55;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerBBtn.setTexture(m_redTex);
				playerIDs.at(1) = m_redID;
				m_playerBBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerBBtn.setTexture(m_yellowTex);
				playerIDs.at(1) = m_yellowID;
				m_playerBBtn.m_playerID = 55;
				m_yellowID = m_lockedInID;
				checkIDs(3);
				lockedB = true;
			}
		}

		if (id == m_playerThreeID && lockedC == false)
		{
			if (m_playerCBtn.m_playerID == m_blueID)
			{
				m_blueTex = ResourceManager::getInstance()->getTextureByKey("greyedBlue");
				m_playerCBtn.setTexture(m_blueTex);
				playerIDs.at(2) = m_blueID;
				m_playerCBtn.m_playerID = 55;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerCBtn.setTexture(m_greenTex);
				playerIDs.at(2) = m_greenID;
				m_playerCBtn.m_playerID = 55;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerCBtn.setTexture(m_redTex);
				playerIDs.at(2) = m_redID;
				m_playerCBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerCBtn.setTexture(m_yellowTex);
				playerIDs.at(2) = m_yellowID;
				m_playerCBtn.m_playerID = 55;
				m_yellowID = m_lockedInID;
				checkIDs(3);
				lockedC = true;
			}
		}

		if (id == m_playerFourID && lockedD == false)
		{
			if (m_playerDBtn.m_playerID == m_blueID)
			{
				m_blueTex = ResourceManager::getInstance()->getTextureByKey("greyedBlue");
				m_playerDBtn.setTexture(m_blueTex);
				playerIDs.at(3) = m_blueID;
				m_playerDBtn.m_playerID = m_lockedInID;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerDBtn.setTexture(m_greenTex);
				playerIDs.at(3) = m_greenID;
				m_playerDBtn.m_playerID = m_lockedInID;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerDBtn.setTexture(m_redTex);
				playerIDs.at(3) = m_redID;
				m_playerDBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerDBtn.setTexture(m_yellowTex);
				playerIDs.at(3) = m_yellowID;
				m_playerDBtn.m_playerID = 55;
				m_yellowID = m_lockedInID;
				checkIDs(3);
				lockedD = true;
			}
		}

		if (lockedA == true && lockedB == true || m_controllerTwoConnected == false && lockedC == true || m_controllerThreeConnected == false && lockedD == true || m_controllerFourConnected == false)
		{
			loadLevelSelect(Scenes::LEVELSELECT, playerIDs);
		}
	}
}