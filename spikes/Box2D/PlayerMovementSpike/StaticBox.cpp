#include "stdafx.h"
#include "StaticBox.h"


StaticBox::StaticBox(float xPos, float yPos, float width, float height, b2World* world)
{
	m_bodyDef.position.Set(xPos, yPos);

	m_body = world->CreateBody(&m_bodyDef);

	m_box.SetAsBox(width/2, height/2);

	m_body->CreateFixture(&m_box, 0.0f);

	m_rect.x = xPos;
	m_rect.y = yPos;
	m_rect.w = width;
	m_rect.h = height;
}


StaticBox::~StaticBox()
{
}

SDL_Rect* StaticBox::getRect()
{
	return &m_rect;
}
