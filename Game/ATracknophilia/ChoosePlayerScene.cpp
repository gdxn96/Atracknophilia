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
	, lockedA(false)
	, lockedB(false)
	, lockedC(false)
	, lockedD(false)
	, m_blueID(0)
	, m_greenID(1)
	, m_redID(2)
	, m_yellowID(3)
	, m_lockedInID(99)
	
{
	m_playerABtn = Button();
	m_playerBBtn = Button();
	m_playerCBtn = Button();
	m_playerDBtn = Button();
	//m_highlightedBtn = Button();
	loadMedia();
}

void ChoosePlayerScene::update(float dt)
{
	currentTick += dt * 1000; // dt was rounding down to 0 when adding 0.0001 of a second so converting into milliseonds
	if (lockedA && lockedB && lockedC && lockedD)
		changeScene(Scenes::LEVELSELECT);
}

void ChoosePlayerScene::render(Renderer & r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_playerABtn.render(r);
	m_playerBBtn.render(r);
	m_playerCBtn.render(r);
	m_playerDBtn.render(r);
	m_blueHighlightBtn.render(r);
	m_greenHighlightBtn.render(r);
	m_yellowHighlightBtn.render(r);
	m_redHighlightBtn.render(r);
	//m_highlightedBtn.render(r);
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

	m_blueTex = ResourceManager::getInstance()->getTextureByKey("playerAbtn");
	m_greenTex = ResourceManager::getInstance()->getTextureByKey("playerBbtn");
	m_redTex = ResourceManager::getInstance()->getTextureByKey("playerCbtn");
	m_yellowTex = ResourceManager::getInstance()->getTextureByKey("playerDbtn");

	m_playerABtn.setTexture(m_blueTex);
	m_playerBBtn.setTexture(m_greenTex);
	m_playerCBtn.setTexture(m_redTex);
	m_playerDBtn.setTexture(m_yellowTex);

	m_playerABtn.m_playerID = m_playerOneID;
	m_playerBBtn.m_playerID = m_playerTwoID;
	m_playerCBtn.m_playerID = m_playerThreeID;
	m_playerDBtn.m_playerID = m_playerFourID;


	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));
	m_blueHighlightBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("bluehighlight"));
	m_greenHighlightBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("greenhighlight"));
	m_redHighlightBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("redhighlight"));
	m_yellowHighlightBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("yellowhighlight"));
	

	//m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new PressCommand(std::bind(&ChoosePlayerScene::changeScene, this, Scenes::SPLASH)), this, m_playerOneID);
	
	// player 1
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerOneID)), this, m_playerOneID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerOneID)), this, m_playerOneID);

	// player2
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerTwoID)), this, m_playerTwoID);

	// player3
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerThreeID)), this, m_playerThreeID);

	// player4
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerFourID)), this, m_playerFourID);
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

void ChoosePlayerScene::changeCharacter(direction dir, IDs id)
{
	if (id == m_playerOneID)
	{
		if (dir == left)
		{
			m_playerABtn.m_playerID--;
			if (m_playerABtn.m_playerID < 0)
			{
				m_playerABtn.m_playerID = 4;
			}
		}
		if (dir == right)
		{
			m_playerABtn.m_playerID++;
			if (m_playerABtn.m_playerID > 4)
			{
				m_playerABtn.m_playerID = 0;
			}
		}
	}
	if (id == m_playerTwoID)
	{
		if (dir == left)
		{
			m_playerBBtn.m_playerID--;
			if (m_playerBBtn.m_playerID < 0)
			{
				m_playerBBtn.m_playerID = 4;
			}
		}
		if (dir == right)
		{
			m_playerBBtn.m_playerID++;
			if (m_playerBBtn.m_playerID > 4)
			{
				m_playerBBtn.m_playerID = 0;
			}
		}
	}
	if (id == m_playerThreeID)
	{
		if (dir == left)
		{
			m_playerCBtn.m_playerID--;
			if (m_playerCBtn.m_playerID < 0)
			{
				m_playerCBtn.m_playerID = 4;
			}
		}
		if (dir == right)
		{
			m_playerCBtn.m_playerID++;
			if (m_playerCBtn.m_playerID > 4)
			{
				m_playerCBtn.m_playerID = 0;
			}
		}
	}
	if (id == m_playerFourID)
	{
		if (dir == left)
		{
			m_playerDBtn.m_playerID--;
			if (m_playerDBtn.m_playerID < 0)
			{
				m_playerDBtn.m_playerID = 4;
			}
		}
		if (dir == right)
		{
			m_playerDBtn.m_playerID++;
			if (m_playerDBtn.m_playerID > 4)
			{
				m_playerDBtn.m_playerID = 0;
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
				m_blueID = m_lockedInID;
				m_playerABtn.m_playerID = 55;  // set player id to any number greater than 4 so it will never be available to select again
				checkIDs(0);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerABtn.setTexture(m_greenTex);
				m_greenID = m_lockedInID;
				m_playerABtn.m_playerID = 55;
				checkIDs(1);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerABtn.setTexture(m_redTex);
				m_redID = m_lockedInID;
				m_playerABtn.m_playerID = 55;
				checkIDs(2);
				lockedA = true;
			}
			else if (m_playerABtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerABtn.setTexture(m_yellowTex);
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
				m_playerBBtn.m_playerID = 55;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerBBtn.setTexture(m_greenTex);
				m_playerBBtn.m_playerID = 55;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerBBtn.setTexture(m_redTex);
				m_playerBBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedB = true;
			}
			else if (m_playerBBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerBBtn.setTexture(m_yellowTex);
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
				m_playerCBtn.m_playerID = 55;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerCBtn.setTexture(m_greenTex);
				m_playerCBtn.m_playerID = 55;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerCBtn.setTexture(m_redTex);
				m_playerCBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedC = true;
			}
			else if (m_playerCBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerCBtn.setTexture(m_yellowTex);
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
				m_playerDBtn.m_playerID = m_lockedInID;
				m_blueID = m_lockedInID;
				checkIDs(0);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_greenID)
			{
				m_greenTex = ResourceManager::getInstance()->getTextureByKey("greyedGreen");
				m_playerDBtn.setTexture(m_greenTex);
				m_playerDBtn.m_playerID = m_lockedInID;
				m_greenID = m_lockedInID;
				checkIDs(1);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_redID)
			{
				m_redTex = ResourceManager::getInstance()->getTextureByKey("greyedRed");
				m_playerDBtn.setTexture(m_redTex);
				m_playerDBtn.m_playerID = 55;
				m_redID = m_lockedInID;
				checkIDs(2);
				lockedD = true;
			}
			else if (m_playerDBtn.m_playerID == m_yellowID)
			{
				m_yellowTex = ResourceManager::getInstance()->getTextureByKey("greyedYellow");
				m_playerDBtn.setTexture(m_yellowTex);
				m_playerDBtn.m_playerID = 55;
				m_yellowID = m_lockedInID;
				checkIDs(3);
				lockedD = true;
			}
		}
	}
}