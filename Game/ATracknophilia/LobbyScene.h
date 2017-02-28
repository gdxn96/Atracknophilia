#pragma once
#include "SceneManager.h"
#include "Game.h"
#include "Button.h"

class LobbyScene : public Scene, public EventListener
{
public:

	LobbyScene(Vector2D windowSize);

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

	Button m_hostBtn;
	Button m_joinBtn;

	Button m_highlightedBtn;

	// button positions on the screen
	float m_leftBtnPos, m_rightBtnPos, m_yBtnPos;

	// buttons height and weight
	float m_btnWidth, m_btnHeight;

	// controller ID's used to determine player number
	enum IDs { m_playerOneID, m_playerTwoID, m_playerThreeID, m_playerFourID };

	// used for changing character by left or right ordering
	enum direction { left, right };

	void moveHighlightBtn(direction dir, IDs id);

	void executeScene();
};