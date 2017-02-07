#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"

class StaticBox
{
private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_box;

	SDL_Rect m_rect;
public:
	StaticBox();
	StaticBox(float xPos, float yPos, float width, float height, b2World* world);
	~StaticBox();

	SDL_Rect* getRect();
};

