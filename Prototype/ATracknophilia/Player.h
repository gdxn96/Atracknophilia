#pragma once

#pragma once

#include "Vector.h"
#include "sdl/SDL.h"
#include "Box.h"

class Player
{
public:
	Player();
	void Render(SDL_Renderer* r);
	void update(float dt);
	void ApplyForce(Vector v);
private:
	Box m_box;
};

