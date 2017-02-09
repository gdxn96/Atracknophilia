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

		bodyDef.position.Set(x + width / 2.f, y + height / 2.f);
		
		b2PolygonShape shape;
		shape.SetAsBox(width / 2.f, height / 2.f);

		if (m_isStatic)
		{
			bodyDef.type = b2_staticBody;
			m_body = World().CreateBody(&bodyDef);
			m_body->CreateFixture(&shape, 0.f);
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			m_body = World().CreateBody(&bodyDef);
			b2FixtureDef fixture;
			fixture.shape = &shape;
			fixture.density = 1.0f;
			fixture.friction = 0.3f;
			m_fixture = m_body->CreateFixture(&fixture);
		}
	}

	void update(float dt)
	{
		m_rect.x = m_body->GetPosition().x - m_rect.w / 2.f;
		m_rect.y = m_body->GetPosition().y - m_rect.h / 2.f;
	}

	void Render(SDL_Renderer* r)
	{
		if (m_isStatic)
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(r, 0, 255, 0, 255);

		for (b2Fixture* b2Fixture = m_body->GetFixtureList(); b2Fixture != 0; b2Fixture = b2Fixture->GetNext())
		{

			b2Shape::Type shapeType = b2Fixture->GetType();
			if (shapeType == b2Shape::e_circle)
			{
			}
			else if (shapeType == b2Shape::e_polygon)
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)b2Fixture->GetShape();

				int lenght = (int)polygonShape->GetVertexCount();

				SDL_Point* points = new SDL_Point[lenght + 1];


				for (int i = 0; i < lenght; i++)
				{
					Vector worldPoint;
					float verticesPosX = polygonShape->GetVertex(i).x; b2Fixture->GetBody()->GetPosition().x;
					float verticesPosY = polygonShape->GetVertex(i).y; b2Fixture->GetBody()->GetPosition().y;
					/*
					float mag = sqrt(fixturePosX * fixturePosX + fixturePosY * fixturePosY);
					if (mag != 0)
					{
					fixturePosX /= mag;
					fixturePosY /= mag;
					}*/
					float angle = b2Fixture->GetBody()->GetAngle();
					float s = sin(angle);
					float c = cos(angle);

					// translate point back to origin:
					verticesPosX -= 0;
					verticesPosY -= 0;

					// rotate point
					float xnew = verticesPosX* c - verticesPosY * s;
					float ynew = verticesPosX * s + verticesPosY * c;

					// translate point back:
					verticesPosX = xnew + 0;
					verticesPosY = ynew + 0;

					worldPoint.x = verticesPosX + b2Fixture->GetBody()->GetPosition().x;;
					worldPoint.y = verticesPosY + b2Fixture->GetBody()->GetPosition().y;;
					worldPoint = worldPoint * 10;
					points[i].x = worldPoint.x;
					points[i].y = worldPoint.y;
				}

				points[lenght].y = points[0].y;
				points[lenght].x = points[0].x;



				SDL_RenderDrawLines(r, points, lenght + 1);
			}
		}
	}

	SDL_Rect m_rect;
	bool m_isStatic;
	b2Body* m_body;
	b2Fixture* m_fixture;
};