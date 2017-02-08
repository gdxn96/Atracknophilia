#pragma once
#include "LTimer.h"
#include "Renderer.h"

class Game
{
public:
	void init();
	void update(float dt);
	void render();
	static bool quit;	
private:
	Renderer m_renderer;
};
