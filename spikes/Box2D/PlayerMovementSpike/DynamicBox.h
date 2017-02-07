#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"

class DynamicBox
{
private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_box;

	SDL_Rect m_rect;
public:
	DynamicBox();
	~DynamicBox();

	SDL_Rect getRect();
};

