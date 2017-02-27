#include "stdafx.h" 
#include "StartScene.h"

StartScene::StartScene(Vector2D windowSize) 
	: Scene(Scenes::SPLASH)
	, m_textureRect(0, 0, windowSize.x, windowSize.y)
	, m_leftBtnPos(200)
	, m_rightBtnPos(800)
	, m_upBtnPos(350)
	, m_downBtnPos(500)
	, m_btnHeight(50)
	, m_btnWidth(250)
{
	m_startBtn = Button();
	m_creditBtn = Button();
	m_lvlselectBtn = Button();
	m_optionsBtn = Button();
	m_highlightedBtn = Button();
	loadMedia();
}

void StartScene::update(float dt)
{
	// do button highlighting here
}

void StartScene::render(Renderer& r)
{
	r.drawTexture(m_splashScreen, m_textureRect);
	m_startBtn.render(r);
	m_creditBtn.render(r);
	m_lvlselectBtn.render(r);
	m_optionsBtn.render(r);
	m_highlightedBtn.render(r);
	r.present();
}

bool StartScene::init(Renderer & r)
{
	// init success flag
	bool success = true;

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

	/*InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new HoldCommand([&]() {
		
	}), this, 1);*/

	//Load splash image here..
	m_splashScreen = ResourceManager::getInstance()->getTextureByKey("startscreen");

	m_startBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_creditBtn.setRect(Rect{ m_rightBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });
	m_lvlselectBtn.setRect(Rect{ m_leftBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_optionsBtn.setRect(Rect{ m_rightBtnPos, m_downBtnPos, m_btnWidth, m_btnHeight });
	m_highlightedBtn.setRect(Rect{ m_leftBtnPos, m_upBtnPos, m_btnWidth, m_btnHeight });

	m_startBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("startgamebtn"));
	m_creditBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("creditsbtn"));
	m_lvlselectBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("levelselectbtn"));
	m_optionsBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("optionsbtn"));
	m_highlightedBtn.setTexture(ResourceManager::getInstance()->getTextureByKey("highlight"));

	m_highlightedBtn.setDirection(left);

	// set key binds
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_LEFT, new PressCommand(std::bind(&StartScene::moveHighlightBtn, this, left)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_RIGHT, new PressCommand(std::bind(&StartScene::moveHighlightBtn, this, right)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_UP, new PressCommand(std::bind(&StartScene::moveHighlightBtn, this, up)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_DPAD_DOWN, new PressCommand(std::bind(&StartScene::moveHighlightBtn, this, down)), this, 0);
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand(std::bind(&StartScene::executeScene, this, m_highlightedBtn.getRect())), this, 0);

	return success;
}

void StartScene::moveHighlightBtn(direction dir)
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
	if(dir == right && m_highlightedBtn.getDirection() != right)
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

void StartScene::executeScene(Rect highlightedBtn)
{
	if (m_startBtn.getRect() == highlightedBtn)
	{
		// do start btn logic
		changeScene(Scenes::GAME);
	}
	if (m_creditBtn.getRect() == highlightedBtn)
	{
		// do credits btn logic
	}
	if (m_lvlselectBtn.getRect() == highlightedBtn)
	{
		// do lvl select btn logic
	}
	if (m_optionsBtn.getRect() == highlightedBtn)
	{
		// do options btn logic
	}
}
