#pragma once
#include "Renderer.h"

class Button
{
public:
	Button();
	Button(Rect buttonRect);

	void render(Renderer& r);

	void setRect(Rect buttonRect);

	void setTexture(SDL_Texture* texture);

	void setDirection(float dir);

	float getDirection();

	Rect getRect();

	//enum colour { blue, green, red, yellow };

	//void setColour(colour c);

	//colour m_col;

	int m_playerID = NULL;
private:

	SDL_Texture* m_texture = NULL;
	Rect m_textureRect;
	float m_direction;
};