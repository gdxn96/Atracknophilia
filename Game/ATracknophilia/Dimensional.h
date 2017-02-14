#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"
#include "Animation.h"
#include "PhysicsSystem.h"

struct Box2DComponent : public AutoLister<Box2DComponent>, public IComponent
{
	Box2DComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true) 
		:	IComponent(id) 
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
			afixture.friction = 0.3f;
			fixture = body->CreateFixture(&afixture);
		}
		body->SetUserData(this);
	}
	virtual ~Box2DComponent() {
		PhysicsSystem::World().DestroyBody(body);
	};

	b2Body* body;
	b2Fixture* fixture;
};

struct CollisionBoxComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	CollisionBoxComponent(int id, float x, float y, float width, float height, bool isStatic=true, bool fixedRotation=true) 
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

struct SoftObstacleComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	SoftObstacleComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true)
		: Box2DComponent(id, x, y, width, height, isStatic, fixedRotation)
	{
		fixture->SetSensor(true);
	}
};

