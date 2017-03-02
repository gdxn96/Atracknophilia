#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "Drawables.h"
#include "PhysicsSystem.h"

struct HookComponent : public IComponent, public AutoLister<HookComponent>
{
	HookComponent(int id, Vector2D start, Vector2D end, b2Body* bodyToAttach) 
		:	IComponent(id)
		,	pivot( new StaticBodyComponent(-1, end.x, end.y, 0, 0, true))
		,	tetherLength(Vector2D::Distance(start, end) * 0.9f)
		,	line(new LineComponent(-1, start, end))
		,	alive(true)
	{
		b2DistanceJointDef jointDef;
		jointDef.bodyA = bodyToAttach;
		jointDef.bodyB = pivot->body;
		jointDef.collideConnected = false;
		jointDef.length = tetherLength;
		jointDef.dampingRatio = 0.5;
		jointDef.frequencyHz = 60;

		joint = (b2DistanceJoint*)PhysicsSystem::World().CreateJoint(&jointDef);
	}

	void decreaseTetherLength(float dt)
	{
		tetherLength -= 30 * dt;
		joint->SetLength(tetherLength);
	}

	void increaseTetherLength(float dt)
	{
		tetherLength += 2 * dt;
		joint->SetLength(tetherLength);
	}

	virtual ~HookComponent()
	{
		PhysicsSystem::World().DestroyJoint(joint);
		delete pivot;
		delete line;
	}

	b2DistanceJoint* joint;
	Box2DComponent* pivot;
	LineComponent* line;
	float tetherLength;
	bool alive;
};

//struct AbilityComponent : public IComponent, public AutoLister<AbilityComponent>
//{
//	enum ABILITIES {
//		NONE,
//		WEB_DROP,
//		SLOW_SHOT,
//		SWAP_SHOT
//	};
//
//	AbilityComponent(int id)
//		: IComponent(id)
//	{
//	}
//
//	ABILITIES ability = NONE;
//};
