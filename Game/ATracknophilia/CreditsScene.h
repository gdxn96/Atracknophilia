#pragma once
#include "SceneManager.h"
#include "Game.h"

class CreditsScene : public Scene, public EventListener
{
public:

	CreditsScene(Vector2D windowSize);

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
};