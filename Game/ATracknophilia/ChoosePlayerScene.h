#pragma once
#include "SceneManager.h"
#include "Game.h"
#include "Button.h"

class ChoosePlayerScene : public Scene, public EventListener
{
public:
	ChoosePlayerScene(Vector2D windowSize);

	void update(float dt) override;
	void render(Renderer& r) override;

	bool init(Renderer & r) override;
	void changeScene(Scenes newScene) override;
private:
	bool loadMedia();

	//The image we will load and show on the screen
	SDL_Texture* m_splashScreen = NULL;
	Rect m_textureRect;
	Button m_playerABtn;
	Button m_playerBBtn;
	Button m_playerCBtn;
	Button m_playerDBtn;

	Button m_highlightedBtn;

	float m_leftBtnPos, m_rightBtnPos, m_upBtnPos, m_downBtnPos;

	float m_btnWidth, m_btnHeight;

	enum direction { left, right, up, down };
	void moveHighlightBtn(direction dir);

	void executeScene();
};