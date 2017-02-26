#pragma once
#include "Renderer.h"

class Button
{
public:
	Button();
	Button(Rect buttonRect);

	void render(Renderer& r);

	void setRect(Rect buttonRect);

private:

	bool loadContent();

	SDL_Texture* m_texture = NULL;
	Rect m_textureRect;
};