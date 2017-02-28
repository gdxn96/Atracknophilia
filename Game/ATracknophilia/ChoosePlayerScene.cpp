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
	, m_currentColour(0)
	, lockedA(false)
	, lockedB(false)
	, lockedC(false)
	, lockedD(false)
	, m_blueID(0)
	, m_greenID(1)
	, m_redID(2)
	, m_yellowID(3)
	
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

	//m_playerABtn.setColour(Button::colour::blue);
	//m_playerBBtn.setColour(Button::colour::green);
	//m_playerCBtn.setColour(Button::colour::yellow);
	//m_playerDBtn.setColour(Button::colour::red);

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
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerOneID)), this, m_playerOneID);

	// player2
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerTwoID)), this, m_playerTwoID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerTwoID)), this, m_playerTwoID);

	// player3
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerThreeID)), this, m_playerThreeID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerThreeID)), this, m_playerThreeID);

	// player4
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, left, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&ChoosePlayerScene::changePlayerColour, this, right, m_playerFourID)), this, m_playerFourID);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&ChoosePlayerScene::executeScene, this, m_playerFourID)), this, m_playerFourID);

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

void ChoosePlayerScene::changePlayerColour(direction dir, int controllerId)
{
	Button::colour c;
	switch (controllerId)
	{
	case m_playerOneID:
		c = updateCurrentColour(dir);
		updatePlayer(c, m_playerOneID);
		break;
	case m_playerTwoID:
		c = updateCurrentColour(dir);
		updatePlayer(c, m_playerTwoID);
		break;
	case m_playerThreeID:
		c = updateCurrentColour(dir);
		updatePlayer(c, m_playerThreeID);
		break;
	case m_playerFourID:
		c = updateCurrentColour(dir);
		updatePlayer(c, m_playerFourID);
		break;
	}
}

void ChoosePlayerScene::updatePlayer(Button::colour c, IDs id)
{
	if (id == m_playerOneID && lockedA == false)
	{
		if (c == Button::colour::blue) { m_playerABtn.setTexture(m_blueTex); m_playerABtn.setColour(Button::colour::blue); }
		if (c == Button::colour::green) { m_playerABtn.setTexture(m_greenTex); m_playerABtn.setColour(Button::colour::green);}
		if (c == Button::colour::red) { m_playerABtn.setTexture(m_redTex); m_playerABtn.setColour(Button::colour::red); }
		if (c == Button::colour::yellow) { m_playerABtn.setTexture(m_yellowTex); m_playerABtn.setColour(Button::colour::yellow);}
	}
	if (id == m_playerTwoID && lockedB == false)
	{
		if (c == Button::colour::blue) { m_playerBBtn.setTexture(m_blueTex); m_playerBBtn.setColour(Button::colour::blue); }
		if (c == Button::colour::green) { m_playerBBtn.setTexture(m_greenTex); m_playerBBtn.setColour(Button::colour::green); }
		if (c == Button::colour::red) { m_playerBBtn.setTexture(m_redTex); m_playerBBtn.setColour(Button::colour::red); }
		if (c == Button::colour::yellow) { m_playerBBtn.setTexture(m_yellowTex); m_playerBBtn.setColour(Button::colour::yellow); }
	}
	if (id == m_playerThreeID && lockedC == false)
	{
		if (c == Button::colour::blue) { m_playerCBtn.setTexture(m_blueTex); m_playerCBtn.setColour(Button::colour::blue); }
		if (c == Button::colour::green) { m_playerCBtn.setTexture(m_greenTex); m_playerCBtn.setColour(Button::colour::green); }
		if (c == Button::colour::red) { m_playerCBtn.setTexture(m_redTex); m_playerCBtn.setColour(Button::colour::red); }
		if (c == Button::colour::yellow) { m_playerCBtn.setTexture(m_yellowTex); m_playerCBtn.setColour(Button::colour::yellow); }
	}
	if (id == m_playerFourID && lockedD == false)
	{
		if (c == Button::colour::blue) { m_playerDBtn.setTexture(m_blueTex); m_playerDBtn.setColour(Button::colour::blue); }
		if (c == Button::colour::green) { m_playerDBtn.setTexture(m_greenTex); m_playerDBtn.setColour(Button::colour::green); }
		if (c == Button::colour::red) { m_playerDBtn.setTexture(m_redTex); m_playerDBtn.setColour(Button::colour::red); }
		if (c == Button::colour::yellow) { m_playerDBtn.setTexture(m_yellowTex); m_playerDBtn.setColour(Button::colour::yellow); }
	}
}

Button::colour ChoosePlayerScene::updateCurrentColour(direction dir)
{
	if (dir == left)
	{
		m_currentColour--;
		if (m_currentColour < 0) { m_currentColour = 4; }
	}
	if (dir == right)
	{
		m_currentColour++;
		if (m_currentColour > 4) { m_currentColour = 0; }
	}
	

	if (m_currentColour == m_blueID) { return Button::colour::blue; }
	else if (m_blueID == 888) { return Button::colour::green; }
	if (m_currentColour == m_greenID) { return Button::colour::green; }
	else if (m_greenID == 888) { return Button::colour::red; }
	if (m_currentColour == m_redID) { return Button::colour::red; }
	else if (m_redID == 888) { return Button::colour::yellow; }
	if (m_currentColour == m_yellowID) { return Button::colour::yellow; }
	else if (m_yellowID == 888) { return Button::colour::blue; }
}



void ChoosePlayerScene::executeScene(IDs id)
{
	if (id == m_playerOneID && lockedA == false)
	{
		if (m_playerABtn.m_col == Button::colour::blue && m_blueID != 888) { m_blueHighlightBtn.setRect(m_playerABtn.getRect());  m_blueID = 888; }
		if (m_playerABtn.m_col == Button::colour::green && m_greenID != 888) { m_greenHighlightBtn.setRect(m_playerABtn.getRect()); m_greenID = 888; }
		if (m_playerABtn.m_col == Button::colour::red && m_redID != 888) { m_redHighlightBtn.setRect(m_playerABtn.getRect());  m_redID = 888; }
		if (m_playerABtn.m_col == Button::colour::yellow && m_yellowID != 888) { m_yellowHighlightBtn.setRect(m_playerABtn.getRect()); m_yellowID = 888;}
		lockedA = true;
	}
	if (id == m_playerTwoID && lockedB == false)
	{
		if (m_playerBBtn.m_col == Button::colour::blue && m_blueID != 888) { m_blueHighlightBtn.setRect(m_playerBBtn.getRect()); m_blueID = 888;}
		if (m_playerBBtn.m_col == Button::colour::green && m_greenID != 888) { m_greenHighlightBtn.setRect(m_playerBBtn.getRect()); m_greenID = 888;}
		if (m_playerBBtn.m_col == Button::colour::red && m_redID != 888) { m_redHighlightBtn.setRect(m_playerBBtn.getRect()); m_redID = 888;}
		if (m_playerBBtn.m_col == Button::colour::yellow && m_yellowID != 888) { m_yellowHighlightBtn.setRect(m_playerBBtn.getRect()); m_yellowID = 888;}
		lockedB = true;
	}
	if (id == m_playerThreeID && lockedC == false)
	{
		if (m_playerCBtn.m_col == Button::colour::blue && m_blueID != 888) { m_blueHighlightBtn.setRect(m_playerCBtn.getRect());  m_blueID = 888;}
		if (m_playerCBtn.m_col == Button::colour::green && m_greenID != 888) { m_greenHighlightBtn.setRect(m_playerCBtn.getRect()); m_greenID = 888;}
		if (m_playerCBtn.m_col == Button::colour::red && m_redID != 888) { m_redHighlightBtn.setRect(m_playerCBtn.getRect()); m_redID = 888;}
		if (m_playerCBtn.m_col == Button::colour::yellow && m_yellowID != 888) { m_yellowHighlightBtn.setRect(m_playerCBtn.getRect()); m_yellowID = 888;}
		lockedC = true;
	}
	if (id == m_playerFourID && lockedD == false)
	{
		if (m_playerDBtn.m_col == Button::colour::blue && m_blueID != 888) { m_blueHighlightBtn.setRect(m_playerDBtn.getRect()); m_blueID = 888;}
		if (m_playerDBtn.m_col == Button::colour::green && m_greenID != 888) { m_greenHighlightBtn.setRect(m_playerDBtn.getRect()); m_greenID = 888;}
		if (m_playerDBtn.m_col == Button::colour::red && m_redID != 888) { m_redHighlightBtn.setRect(m_playerDBtn.getRect()); m_redID = 888;}
		if (m_playerDBtn.m_col == Button::colour::yellow && m_yellowID != 888) { m_yellowHighlightBtn.setRect(m_playerDBtn.getRect()); m_yellowID = 888;}
		lockedD = true;
	}
}