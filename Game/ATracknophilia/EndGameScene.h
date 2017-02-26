#pragma once
#include "SceneManager.h"
#include "Game.h"

class EndGameScene : public Scene
{
public:
	EndGameScene(Vector2D windowSize);

	//can be overriden

	void update(float dt) override;
	void render(Renderer& r) override;
	bool init(Renderer & r) override;
	void changeScene(Scenes newScene) override;
private:
	bool loadMedia();

	//The image we will load and show on the screen
	SDL_Texture* m_splashScreen = NULL;
	int currentTick = 0;
	Vector2D m_windowSize;
};