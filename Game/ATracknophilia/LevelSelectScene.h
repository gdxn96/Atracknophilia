#pragma once
#include "SceneManager.h"
#include "Game.h"
#include "Button.h"

class LevelSelectScene : public Scene, public EventListener
{
public:

	LevelSelectScene(Vector2D windowSize);

	void update(float dt) override;
	void render(Renderer& r) override;
	bool init(Renderer & r) override;
	void changeScene(Scenes newScene) override;

private:

	bool loadMedia();

	//The image we will load and show on the screen
	SDL_Texture* m_splashScreen = NULL;
	Rect m_textureRect;
	int currentTick = 0;

	Button m_lvl1Btn;
	Button m_lvl2Btn;
	Button m_lvl3Btn;
	Button m_lvl4Btn;

	Button m_highlightedBtn;

	float m_leftBtnPos, m_rightBtnPos, m_upBtnPos, m_downBtnPos;

	float m_btnWidth, m_btnHeight;

	enum direction { left, right, up, down };
	void moveHighlightBtn(direction dir);

	void executeScene();
};