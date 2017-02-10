#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"
#include "Animation.h"

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
	virtual ~Box2DComponent() {};

	b2Body* body;
	b2Fixture* fixture;
};

struct CollisionBoxComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	CollisionBoxComponent(int id, float x, float y, float width, float height, bool isStatic=true, bool fixedRotation=true) : Box2DComponent(id, x, y, width, height, isStatic, fixedRotation) 
	{
	}
};

struct AnimationComponent : public IComponent, public AutoLister<AnimationComponent>
{
	AnimationComponent(int objectId, Animation a) : IComponent(objectId), animation(a) {};
	Animation animation;
};