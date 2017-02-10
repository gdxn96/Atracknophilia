#pragma once
#include "LTimer.h"
#include "Renderer.h"
#include "ECSInterfaces.h"
#include "Systems.h"

class Game
{
public:
	Game(Vector2D windowSize, Vector2D levelSize, const char* windowName);
	void init();
	void loop(float dt);
	static bool quit;	
private:
	Renderer m_renderer;
	Camera2D m_camera;
	std::vector<ISystem*> m_systems;
};
