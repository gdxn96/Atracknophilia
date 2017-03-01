#include "stdafx.h" 
#include "LevelSelectScene.h"

LevelSelectScene::LevelSelectScene(Vector2D windowSize)
	: Scene(Scenes::LEVELSELECT)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(100)
	, m_rightBtnPos(500)
	, m_upBtnPos(150)
	, m_downBtnPos(500)
	, m_btnHeight(189)
	, m_btnWidth(250)
	, lockedA(false)
	, lockedB(false)
	, lockedC(false)
	, lockedD(false)
	, m_blueID(0)
	, m_greenID(1)
	, m_redID(2)
	, m_yellowID(3)
	, m_lockedInID(99)
	, m_arrowHeight(15)
	, m_arrowWidth(30)
	, m_scaler(1.5)
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
	//m_highlightedBtn = Button();
	loadMedia();
}

void LevelSelectScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
	if (lockedA && lockedB && lockedC && lockedD)
		changeScene(Scenes::LEVELSELECT);
}

void LevelSelectScene::render(Renderer & r)
{
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
	//m_highlightedBtn.render(r);
	r.present();
}

bool LevelSelectScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

	m_playerABtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerBBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_playerCBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_playerDBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });

	m_aLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_aRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_bLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_bRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_upBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_cLeftArrowBtn.setRect(Rect{ m_leftBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_cRightArrowBtn.setRect(Rect{ (m_leftBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_dLeftArrowBtn.setRect(Rect{ m_rightBtnPos - (m_arrowWidth * 2), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });
	m_dRightArrowBtn.setRect(Rect{ (m_rightBtnPos + m_btnWidth) + (m_arrowWidth), m_downBtnPos + (m_btnHeight / 2), m_arrowWidth, m_arrowHeight });

	m_lvlOneTex = ResourceManager::getInstance()->getTextureByKey("lvl1btn");
	m_lvlTwoTex = ResourceManager::getInstance()->getTextureByKey("lvl2btn");
	m_lvlThreeTex = ResourceManager::getInstance()->getTextureByKey("lvl3btn");
	m_lvlFourTex = ResourceManager::getInstance()->getTextureByKey("lvl4btn");

	m_leftArrowTex = ResourceManager::getInstance()->getTextureByKey("arrowleftbtn");
	m_rightArrowTex = ResourceManager::getInstance()->getTextureByKey("arrowrightbtn");

	m_playerABtn.setTexture(m_lvlOneTex);
	m_playerBBtn.setTexture(m_lvlTwoTex);
	m_playerCBtn.setTexture(m_lvlThreeTex);
	m_playerDBtn.setTexture(m_lvlFourTex);

	m_aLeftArrowBtn.setTexture(m_leftArrowTex);
	m_aRightArrowBtn.setTexture(m_rightArrowTex);
	m_bLeftArrowBtn.setTexture(m_leftArrowTex);
	m_bRightArrowBtn.setTexture(m_rightArrowTex);
	m_cLeftArrowBtn.setTexture(m_leftArrowTex);
	m_cRightArrowBtn.setTexture(m_rightArrowTex);
	m_dLeftArrowBtn.setTexture(m_leftArrowTex);
	m_dRightArrowBtn.setTexture(m_rightArrowTex);

	m_playerABtn.m_playerID = m_playerOneID;
	m_playerBBtn.m_playerID = m_playerTwoID;
	m_playerCBtn.m_playerID = m_playerThreeID;
	m_playerDBtn.m_playerID = m_playerFourID;


	//m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&LevelSelectScene::changeScene, this, Scenes::SPLASH)), this, m_playerOneID);

	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LevelSelectScene::executeScene, this, m_playerOneID)), this, m_playerOneID);

	// player2
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LevelSelectScene::executeScene, this, m_playerTwoID)), this, m_playerTwoID);

	// player3
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LevelSelectScene::executeScene, this, m_playerThreeID)), this, m_playerThreeID);

	// player4
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&LevelSelectScene::changePlayerMap, this, right, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new ReleaseCommand(std::bind(&LevelSelectScene::reduceArrowScale, this, right, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&LevelSelectScene::executeScene, this, m_playerFourID)), this, m_playerFourID);

	return success;
}

void LevelSelectScene::changeScene(Scenes newScene)
{
	if (SceneManager::getInstance()->getCurrentScene()->getTitle() == Scenes::LEVELSELECT)
	{
		currentTick = 0;
		SceneManager::getInstance()->switchTo(newScene);
	}

}

bool LevelSelectScene::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("lobbyselect");

	return success;
}

void LevelSelectScene::changePlayerMap(direction dir, int controllerId)
{
	switch (controllerId)
	{
	case m_playerOneID:
		if (lockedA == false) { changeLevel(dir, m_playerOneID); }
		updatePlayer(m_playerABtn.m_playerID, m_playerOneID);
		break;
	case m_playerTwoID:
		if (lockedB == false) { changeLevel(dir, m_playerTwoID); }
		updatePlayer(m_playerBBtn.m_playerID, m_playerTwoID);
		break;
	case m_playerThreeID:
		if (lockedC == false) { changeLevel(dir, m_playerThreeID); }
		updatePlayer(m_playerCBtn.m_playerID, m_playerThreeID);
		break;
	case m_playerFourID:
		if (lockedD == false) { changeLevel(dir, m_playerFourID); }
		updatePlayer(m_playerDBtn.m_playerID, m_playerFourID);
		break;
	}
}

void LevelSelectScene::reduceArrowScale(direction dir, int controllerID)
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

void LevelSelectScene::changeLevel(direction dir, IDs id)
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

void LevelSelectScene::updatePlayer(int buttonID, IDs id)
{
	if (id == m_playerOneID && lockedA == false)
	{
		if (buttonID == 0) { m_playerABtn.setTexture(m_lvlOneTex); }
		if (buttonID == 1) { m_playerABtn.setTexture(m_lvlTwoTex); }
		if (buttonID == 2) { m_playerABtn.setTexture(m_lvlThreeTex); }
		if (buttonID == 3) { m_playerABtn.setTexture(m_lvlFourTex); }
	}
	if (id == m_playerTwoID  && lockedB == false)
	{
		if (buttonID == 0) { m_playerBBtn.setTexture(m_lvlOneTex); }
		if (buttonID == 1) { m_playerBBtn.setTexture(m_lvlTwoTex); }
		if (buttonID == 2) { m_playerBBtn.setTexture(m_lvlThreeTex); }
		if (buttonID == 3) { m_playerBBtn.setTexture(m_lvlFourTex); }
	}
	if (id == m_playerThreeID  && lockedC == false)
	{
		if (buttonID == 0) { m_playerCBtn.setTexture(m_lvlOneTex); }
		if (buttonID == 1) { m_playerCBtn.setTexture(m_lvlTwoTex); }
		if (buttonID == 2) { m_playerCBtn.setTexture(m_lvlThreeTex); }
		if (buttonID == 3) { m_playerCBtn.setTexture(m_lvlFourTex); }
	}
	if (id == m_playerFourID  && lockedD == false)
	{
		if (buttonID == 0) { m_playerDBtn.setTexture(m_lvlOneTex); }
		if (buttonID == 1) { m_playerDBtn.setTexture(m_lvlTwoTex); }
		if (buttonID == 2) { m_playerDBtn.setTexture(m_lvlThreeTex); }
		if (buttonID == 3) { m_playerDBtn.setTexture(m_lvlFourTex); }
	}
}


void LevelSelectScene::executeScene(IDs id)
{
	if (currentTick > 1)
	{
		if (id == m_playerOneID && lockedA == false)
		{
			if (m_playerABtn.m_playerID == m_blueID)
			{
				m_lvlOneTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl1btn");
				m_playerABtn.setTexture(m_lvlOneTex);
				m_playerABtn.m_playerID = 55;  // set player id to any number greater than 4 so it will never be available to select again
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_greenID)
			{
				m_lvlTwoTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl2btn");
				m_playerABtn.setTexture(m_lvlTwoTex);
				m_playerABtn.m_playerID = 55;
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_redID)
			{
				m_lvlThreeTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl3btn");
				m_playerABtn.setTexture(m_lvlThreeTex);
				m_playerABtn.m_playerID = 55;
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_yellowID)
			{
				m_lvlFourTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl4btn");
				m_playerABtn.setTexture(m_lvlFourTex);
				m_playerABtn.m_playerID = 55;
				lockedA = true;
			}
		}

		if (id == m_playerTwoID && lockedB == false)
		{
			if (m_playerBBtn.m_playerID == m_blueID)
			{
				m_lvlOneTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl1btn");
				m_playerBBtn.setTexture(m_lvlOneTex);
				m_playerBBtn.m_playerID = 55;
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_greenID)
			{
				m_lvlTwoTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl2btn");
				m_playerBBtn.setTexture(m_lvlTwoTex);
				m_playerBBtn.m_playerID = 55;
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_redID)
			{
				m_lvlThreeTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl3btn");
				m_playerBBtn.setTexture(m_lvlThreeTex);
				m_playerBBtn.m_playerID = 55;
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_yellowID)
			{
				m_lvlFourTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl4btn");
				m_playerBBtn.setTexture(m_lvlFourTex);
				m_playerBBtn.m_playerID = 55;
				lockedB = true;
			}
		}

		if (id == m_playerThreeID && lockedC == false)
		{
			if (m_playerCBtn.m_playerID == m_blueID)
			{
				m_lvlOneTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl1btn");
				m_playerCBtn.setTexture(m_lvlOneTex);
				m_playerCBtn.m_playerID = 55;
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_greenID)
			{
				m_lvlTwoTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl2btn");
				m_playerCBtn.setTexture(m_lvlTwoTex);
				m_playerCBtn.m_playerID = 55;
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_redID)
			{
				m_lvlThreeTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl3btn");
				m_playerCBtn.setTexture(m_lvlThreeTex);
				m_playerCBtn.m_playerID = 55;
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_yellowID)
			{
				m_lvlFourTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl4btn");
				m_playerCBtn.setTexture(m_lvlFourTex);
				m_playerCBtn.m_playerID = 55;
				lockedC = true;
			}
		}

		if (id == m_playerFourID && lockedD == false)
		{
			if (m_playerDBtn.m_playerID == m_blueID)
			{
				m_lvlOneTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl1btn");
				m_playerDBtn.setTexture(m_lvlOneTex);
				m_playerDBtn.m_playerID = m_lockedInID;
				m_blueID = m_lockedInID;
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_greenID)
			{
				m_lvlTwoTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl2btn");
				m_playerDBtn.setTexture(m_lvlTwoTex);
				m_playerDBtn.m_playerID = m_lockedInID;
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_redID)
			{
				m_lvlThreeTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl3btn");
				m_playerDBtn.setTexture(m_lvlThreeTex);
				m_playerDBtn.m_playerID = 55;
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_yellowID)
			{
				m_lvlFourTex = ResourceManager::getInstance()->getTextureByKey("greyedlvl4btn");
				m_playerDBtn.setTexture(m_lvlFourTex);
				m_playerDBtn.m_playerID = 55;
				lockedD = true;
			}
		}

		if (lockedA == true && lockedB == true && lockedC == true && lockedD == true)
		{
			changeScene(Scenes::GAME); // need to pass/remember character selection and map selection
		}
	}
}