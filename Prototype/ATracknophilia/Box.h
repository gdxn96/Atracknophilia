#pragma once 
#include "box2d\Box2D.h"
#include "sdl\SDL.h"
#include <string>

static SDL_Rect toPixels(SDL_Rect r)
{
	r.x *= 10;
	r.y *= 10;
	r.w *= 10;
	r.h *= 10;

	return r;
}

static b2Vec2& Gravity()
{
	static b2Vec2 gravity(0, 500);
	return gravity;
}

static b2World& World()
{
	static b2World world(Gravity());
	world.SetGravity(Gravity());
	return world;
}

class Box
{
public:
	Box(float x, float y, float width, float height, bool isStatic) :
		m_isStatic(isStatic)
	{
		m_rect.x = x;
		m_rect.y = y;
		m_rect.w = width;
		m_rect.h = height;

		b2BodyDef bodyDef;

		bodyDef.position.Set(x + width / 2, y + height / 2);

		if (m_isStatic)
		{
			bodyDef.type = b2_staticBody;
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
		}

		m_body = World().CreateBody(&bodyDef);
		m_box.SetAsBox(width / 2, height / 2);

		b2FixtureDef fixture;

		fixture.shape = &m_box;
		fixture.density = 1.0f;

		m_body->CreateFixture(&fixture);
	}
	void update(float dt)
	{
		if (!m_isStatic)
		{
			
		}

		m_rect.x = m_body->GetPosition().x - m_rect.w / 2;
		m_rect.y = m_body->GetPosition().y - m_rect.h / 2;
	}

	void Render(SDL_Renderer* r)
	{
		if (m_isStatic)
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(r, 0, 255, 0, 255);

		SDL_RenderDrawRect(r, &toPixels(m_rect));
	}

	SDL_Rect m_rect;
	bool m_isStatic;
	b2Body* m_body;
	b2PolygonShape m_box;
};