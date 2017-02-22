#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "box2d\Box2D.h"
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
			fixture = body->CreateFixture(&shape, 0.5f);
		}
		else if (type == b2_dynamicBody)
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			body = PhysicsSystem::World().CreateBody(&bodyDef);
			b2FixtureDef afixture;
			afixture.shape = &shape;
			afixture.density = 1.0f;
			afixture.friction = 0.0f;
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

struct Box2DPolyComponent : public AutoLister<Box2DPolyComponent>, public IComponent
{
	Box2DPolyComponent(int id, std::vector<b2Vec2> points, bool isStatic = true, bool fixedRotation = true) : IComponent(id)
{
	b2BodyDef bodyDef;

	b2Vec2 vec[16];

	for (int i = 0; i < points.size(); i++)
	{
		vec[i].Set(points.at(i).x, points.at(i).y);
	}

	bodyPoly.Set(&vec[0], points.size());

	if (isStatic)
	{
		bodyDef.type = b2_staticBody;
		body = PhysicsSystem::World().CreateBody(&bodyDef);
		body->CreateFixture(&bodyPoly, 0.5f);
	}
	else
	{
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = fixedRotation;
		body = PhysicsSystem::World().CreateBody(&bodyDef);
		b2FixtureDef afixture;
		afixture.shape = &bodyPoly;
		afixture.density = 0.5;
		afixture.friction = 0.5;
		afixture.restitution = 0.5;
		fixture = body->CreateFixture(&afixture);
	}
}
virtual ~Box2DPolyComponent()
{
	PhysicsSystem::World().DestroyBody(body);
};

b2Body* body;
b2Fixture* fixture;
b2PolygonShape bodyPoly;
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

struct StaticPolyComponent : public Box2DPolyComponent, public AutoLister<StaticPolyComponent >
{
	StaticPolyComponent(int id, std::vector<b2Vec2> points, bool isStatic = true, bool fixedRotation = true)
		: Box2DPolyComponent(id, points, isStatic, fixedRotation)
	{

	}
};

struct SensorComponent : public KinematicBodyComponent, public AutoLister<SensorComponent>
{
	SensorComponent(int id, float x, float y, float width, float height)
		: KinematicBodyComponent(id, x, y, width, height)
	{
		fixture->SetSensor(true);
		fixture->SetFriction(0);
		fixture->SetDensity(0);
	}
};

struct SlowShotComponent : public DynamicBodyComponent, public AutoLister<SlowShotComponent>
{
	SlowShotComponent(int id, float x, float y, float width, float height, bool isGravity = true, bool fixedRotation = true) : DynamicBodyComponent(id, x, y, width, height, fixedRotation)
	{
		if (!isGravity)
		{
			body->SetGravityScale(0);
			fixture->SetDensity(0);
			body->ResetMassData();
		}
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
