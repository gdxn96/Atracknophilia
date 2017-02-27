#include "stdafx.h"
#include "Button.h"
#include "Systems.h"


Button::Button()
{
	
}

Button::Button(Rect buttonRect)
	:	m_textureRect(buttonRect)
{

}

void Button::render(Renderer & r)
{
	r.drawTexture(m_texture, m_textureRect);
}

void Button::setRect(Rect buttonRect)
{
	m_textureRect = buttonRect;
}

void Button::setTexture(SDL_Texture * texture)
{
	m_texture = texture;
}

float Button::getDirection()
{
	return m_direction;
}

Rect Button::getRect()
{
	return m_textureRect;
}

void Button::setDirection(float dir)
{
	m_direction = dir;
}
