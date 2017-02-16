#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"
#include "Animation.h"
#include "PhysicsSystem.h"

struct Box2DComponent : public AutoLister<Box2DComponent>, public IComponent
{
	Box2DComponent(int id, float x, float y, float width, float height, b2BodyType type=b2_staticBody, bool fixedRotation = true) 
		:	IComponent(id) 
		,	size(width, height)
	{
		b2BodyDef bodyDef;

		bodyDef.position.Set(x + width / 2.f, y + height / 2.f);

		b2PolygonShape shape;
		shape.SetAsBox(width / 2.f, height / 2.f);

		if (type == b2_staticBody)
		{
			bodyDef.type = b2_staticBody;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			fixture = body->CreateFixture(&shape, 0.f);
		}
		else if (type == b2_dynamicBody)
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
		else if (type == b2_kinematicBody)
		{
			bodyDef.type = b2_kinematicBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.1f;
			afixture.isSensor = true;
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

struct StaticBodyComponent : public Box2DComponent, public AutoLister<StaticBodyComponent>
{
	StaticBodyComponent(int id, float x, float y, float width, float height, bool fixedRotation=true)
		:	Box2DComponent(id, x, y, width, height, b2_staticBody, fixedRotation) 
	{
	}
};

struct DynamicBodyComponent : public Box2DComponent, public AutoLister<DynamicBodyComponent>
{
	DynamicBodyComponent(int id, float x, float y, float width, float height, bool fixedRotation = true)
		: Box2DComponent(id, x, y, width, height, b2_dynamicBody, fixedRotation)
	{
	}
};

struct KinematicBodyComponent : public Box2DComponent, public AutoLister<KinematicBodyComponent>
{
	KinematicBodyComponent(int id, float x, float y, float width, float height, bool fixedRotation = true)
		: Box2DComponent(id, x, y, width, height, b2_kinematicBody, fixedRotation)
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

struct SensorComponent : public KinematicBodyComponent, public AutoLister<SensorComponent>
{
	SensorComponent(int id, float x, float y, float width, float height)
		: KinematicBodyComponent(id, x, y, width, height)
	{
	}
};

