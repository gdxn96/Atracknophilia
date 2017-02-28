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

	// buttons used to represent the different player sprite options
	Button m_playerABtn;
	Button m_playerBBtn;
	Button m_playerCBtn;
	Button m_playerDBtn;

	Button m_highlightedBtn;

	// displaying visual feedback to the chosen character
	Button m_blueHighlightBtn, m_greenHighlightBtn, m_yellowHighlightBtn, m_redHighlightBtn;

	// player has locked in their character so do not allow them to change it
	bool lockedA, lockedB, lockedC, lockedD;

	// button positions on the screen
	float m_leftBtnPos, m_rightBtnPos, m_upBtnPos, m_downBtnPos;

	// buttons height and weight
	float m_btnWidth, m_btnHeight;

	// controller ID's used to determine player number
	enum IDs { m_playerOneID, m_playerTwoID, m_playerThreeID, m_playerFourID };

	// used for changing character by left or right ordering
	enum direction { left, right };

	// change the colour of the sprite for the specific player based on their player ID
	void changePlayerColour(direction dir, int controllerId);

	// the current colour each player has selected
	int m_currentColour;

	// the textures used for each different player option
	SDL_Texture* m_blueTex = NULL;
	SDL_Texture* m_greenTex = NULL;
	SDL_Texture* m_redTex = NULL;
	SDL_Texture* m_yellowTex = NULL;
	

	// update the player colour when changed
	void updatePlayer(Button::colour c, IDs id);
	Button::colour updateCurrentColour(direction dir);

	int m_blueID, m_greenID, m_redID, m_yellowID;

	// used to lock in the player's chosen colour character
	void executeScene(IDs id);
};