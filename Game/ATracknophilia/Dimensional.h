#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "PhysicsSystem.h"

struct Box2DComponent : public AutoLister<Box2DComponent>, public IComponent
{
	Box2DComponent(int id, float x, float y, float width, float height, bool isStatic = true, bool fixedRotation = true, bool isSensor = false) : IComponent(id) 
	{
		b2BodyDef bodyDef;

		bodyDef.position.Set(x + width / 2.f, y + height / 2.f);

		b2PolygonShape shape;
		shape.SetAsBox(width / 2.f, height / 2.f);

		if (isStatic && isSensor) //Static sensor
		{
			bodyDef.type = b2_staticBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.isSensor = true;
			afixture.userData = "Sensor";
			body->CreateFixture(&afixture);
		}
		else if (isStatic && !isSensor) //Static box
		{
			bodyDef.type = b2_staticBody;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			body->CreateFixture(&shape, 0.f);
		}
		else if (!isStatic && isSensor) //Dynamic sensor
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.3f;
			afixture.isSensor = true;
			fixture = body->CreateFixture(&afixture);
		}
		else if (!isStatic && !isSensor) //Dynamic box
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.3f;
			afixture.userData = "Player";
			fixture = body->CreateFixture(&afixture);
		}
	}
	virtual ~Box2DComponent() {
		PhysicsSystem::World().DestroyBody(body);
	};

	b2Body* body;
	b2Fixture* fixture;
};

struct CollisionBoxComponent : public Box2DComponent, public AutoLister<CollisionBoxComponent>
{
	CollisionBoxComponent(int id, float x, float y, float width, float height, bool isStatic=true, bool fixedRotation=true, bool isSensor = false) : Box2DComponent(id, x, y, width, height, isStatic, fixedRotation, isSensor)
	{
	}
};