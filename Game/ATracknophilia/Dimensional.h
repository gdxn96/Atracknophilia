#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"

static b2Vec2& Gravity()
{
	static b2Vec2 gravity(0, 0);
	return gravity;
}

static b2World& World()
{
	static b2World world(Gravity());
	world.SetGravity(Gravity());
	return world;
}

struct PositionComponent : public IComponent, public AutoLister<PositionComponent>
{
	PositionComponent(int objectId, Vector2D pos) : IComponent(objectId), position(pos) {};
	Vector2D position;
};

struct AngleComponent : public IComponent, public AutoLister<AngleComponent>
{
	AngleComponent(int objectId, float _angle) : IComponent(objectId), angle(_angle) {};
	float angle;
};

struct SizeComponent : public IComponent, public AutoLister<SizeComponent>
{
	SizeComponent(int objectId, Vector2D _size) : IComponent(objectId), size(_size) {};
	Vector2D size;
};

struct Box2DComponent : public IComponent, public AutoLister<Box2DComponent>
{
	Box2DComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true) : IComponent(id) 
	{
		b2BodyDef bodyDef;

		bodyDef.position.Set(x + width / 2.f, y + height / 2.f);

		b2PolygonShape shape;
		shape.SetAsBox(width / 2.f, height / 2.f);

		if (isStatic)
		{
			bodyDef.type = b2_staticBody;
			body = World().CreateBody(&bodyDef);
			body->CreateFixture(&shape, 0.f);
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			body = World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.3f;
			fixture = body->CreateFixture(&afixture);
		}
	}

	virtual void process() = 0;
	virtual ~Box2DComponent() {};

	b2Body* body;
	b2Fixture* fixture;
};

struct CollisionBoxComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	CollisionBoxComponent(int id, float x, float y, float width, float height, bool isStatic=true, bool fixedRotation=true) : Box2DComponent(id, x, y, width, height, isStatic, fixedRotation) 
	{
	}

	virtual void process() override
	{
		auto pos = getComponent<PositionComponent>();
		if (pos)
		pos->position = body->GetPosition();

		auto angle = getComponent<AngleComponent>();
		if (angle)
		angle->angle = body->GetAngle();
	}
};