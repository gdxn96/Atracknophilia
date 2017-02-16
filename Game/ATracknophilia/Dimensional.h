#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"
#include "Animation.h"
#include "PhysicsSystem.h"

struct Box2DComponent : public AutoLister<Box2DComponent>, public IComponent
{
	Box2DComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true)
		: IComponent(id)
		, size(width, height)
	{
		b2BodyDef bodyDef;

		bodyDef.position.Set(x + width / 2.f, y + height / 2.f);

		b2PolygonShape shape;
		shape.SetAsBox(width / 2.f, height / 2.f);

		if (isStatic)
		{
			bodyDef.type = b2_staticBody;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			fixture = body->CreateFixture(&shape, 0.f);
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.1f;
			fixture = body->CreateFixture(&afixture);
		}
		body->SetUserData(this);
	}
	virtual ~Box2DComponent()
	{
		PhysicsSystem::World().DestroyBody(body);
	};

	b2Body* body;
	b2Fixture* fixture;
	Vector2D size;
};

struct CollisionBoxComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	CollisionBoxComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true)
		: Box2DComponent(id, x, y, width, height, isStatic, fixedRotation)
	{
	}
};

struct AnimationComponent : public IComponent, public AutoLister<AnimationComponent>
{
	AnimationComponent(int objectId, string animationName) 
		:	IComponent(objectId)
		,	animation(Animation(animationName)) {};
	Animation animation;
};

struct SensorComponent : public Box2DComponent, public AutoLister<SensorComponent>
{
	SensorComponent(int id, float x, float y, float width, float height)
		: Box2DComponent(id, x, y, width, height, true, true)
	{
		fixture->SetSensor(true);
	}
};

struct DirectionComponent : public IComponent, public AutoLister<DirectionComponent>
{
	DirectionComponent(int id, Vector2D direction)
		: IComponent(id)
		, m_direction(direction)
	{
	}

	Vector2D m_direction;
};