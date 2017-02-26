#include "stdafx.h"
#include "Button.h"
#include "Systems.h"


Button::Button()
{
	loadContent();
}

Button::Button(Rect buttonRect)
	:	m_textureRect(buttonRect)
{
	loadContent();
}

void Button::render(Renderer & r)
{
	r.drawTexture(m_texture, m_textureRect);
	r.present();
}

void Button::setRect(Rect buttonRect)
{
	m_textureRect = buttonRect;
}

bool Button::loadContent()
{
	//Loading success flag
	bool success = true;

	m_texture = ResourceManager::getInstance()->getTextureByKey("startscreen");

	return success;
}
