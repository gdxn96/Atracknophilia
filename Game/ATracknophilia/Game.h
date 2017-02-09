#pragma once
#include "LTimer.h"
#include "Renderer.h"
#include "Animation.h"

class Game
{
public:
	Game(Vector2D windowSize, Vector2D levelSize, const char* windowName);
	void init();
	void update(float dt);
	void render();
	static bool quit;	
private:
	Renderer m_renderer;
	Camera2D m_camera;
	ResourceManager* m_resourceMan;
};
