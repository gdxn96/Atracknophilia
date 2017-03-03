#pragma once
#include "SceneManager.h"
#include "Game.h"
#include "Button.h"

class LevelSelectScene;
class ChoosePlayerScene : public Scene, public EventListener
{
public:
	ChoosePlayerScene(Vector2D windowSize);

	void update(float dt) override;
	void render(Renderer& r) override;
	void enter() override;
	bool init(Renderer & r) override;
	void changeScene(Scenes newScene) override;
	LevelSelectScene * m_lvl;
private:
	bool loadMedia();
	Vector2D m_windowSize;
	Renderer m_r;
	bool renderInit;
	//The image we will load and show on the screen
	SDL_Texture* m_splashScreen = NULL;
	Rect m_textureRect;
	int currentTick = 0;

	// buttons used to represent the different player sprite options
	Button m_playerABtn;
	Button m_playerBBtn;
	Button m_playerCBtn;
	Button m_playerDBtn;

	Button m_highlightedBtn;

	Button m_aLeftArrowBtn, m_aRightArrowBtn, m_bLeftArrowBtn, m_bRightArrowBtn, m_cLeftArrowBtn, m_cRightArrowBtn, m_dLeftArrowBtn, m_dRightArrowBtn;

	Button m_aiEnabled, m_aiDisabled, m_aiChoice;

	Button m_yIconBtn;

	float m_arrowWidth, m_arrowHeight;

	float m_scaler;

	// player has locked in their character so do not allow them to change it
	bool lockedA, lockedB, lockedC, lockedD;

	// button positions on the screen
	float m_leftBtnPos, m_rightBtnPos, m_upBtnPos, m_downBtnPos;

	float m_aiXPos, m_aiYPos, m_aiHeight;

	bool m_isAiEnabled;

	// buttons height and weight
	float m_btnWidth, m_btnHeight;

	// controller ID's used to determine player number
	enum IDs { m_playerOneID, m_playerTwoID, m_playerThreeID, m_playerFourID };

	// used for changing character by left or right ordering
	enum direction { left, right, up, down};

	// change the colour of the sprite for the specific player based on their player ID
	void changePlayerColour(direction dir, int controllerId);

	// the textures used for each different player option
	SDL_Texture* m_blueTex = NULL;
	SDL_Texture* m_greenTex = NULL;
	SDL_Texture* m_redTex = NULL;
	SDL_Texture* m_yellowTex = NULL;

	SDL_Texture* m_leftArrowTex = NULL;
	SDL_Texture* m_rightArrowTex = NULL;

	SDL_Texture* m_noControllerTex = NULL;

	SDL_Texture* m_aiTex = NULL;

	void moveHighlightedBtn(direction dir);

	void reduceArrowScale(direction dir, int controllerID);
	
	void changeCharacter(direction dir, IDs id);

	// update the player colour when changed
	void updatePlayer(int buttonID, IDs id);

	// the ids used to differentiate between colours
	int m_blueID, m_greenID, m_redID, m_yellowID;

	// assigned to a colourID when locked in to stop others from locking that colour
	int m_lockedInID;

	void checkIDs(int buttonID);

	void checkForControllers();

	bool m_controllerTwoConnected, m_controllerThreeConnected, m_controllerFourConnected;

	void updateAiChoice();

	vector<int> playerIDs;

	void loadLevelSelect(Scenes scene, vector<int> playerIDs);

	// used to lock in the player's chosen colour character
	void executeScene(IDs id);
};