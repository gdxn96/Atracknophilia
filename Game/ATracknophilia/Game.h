#pragma once
#include "LTimer.h"
#include "Renderer.h"
#include "FLInput\FLInputManager.h"

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
	Camera2D::Camera m_camera;

	b2Body* m_body;
	b2PolygonShape m_box;

	b2Body* m_dBody;
	b2PolygonShape m_dBox;
};
