#pragma once
#include "SceneManager.h"
#include "ECSInterfaces.h"
#include "Systems.h"
#include "Animation.h"


class GameScene : public Scene
{
public:
	GameScene();

	void update(float dt) override;
	void render(Renderer& r) override;
	void destroy() override;
	void enter() override;

	bool init(Renderer & r) override;

	void changeScene(Scenes newScene) override;
	
private:  
};