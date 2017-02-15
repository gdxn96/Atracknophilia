#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"
#include "Drawables.h"
#include "PhysicsSystem.h"

struct HookComponent : public IComponent, public AutoLister<HookComponent>
{
	HookComponent(int id, Vector2D start, Vector2D end, b2Body* bodyToAttach) 
		:	IComponent(id)
		,	pivot( new CollisionBoxComponent(-1, end.x, end.y, 1, 1, true, true))
		,	tetherLength(Vector2D::Distance(start, end) * 0.9f)
		,	line(new LineComponent(-1, start, end))
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
		tetherLength -= 100 * dt;
		std::cout << tetherLength << endl;
		joint->SetLength(tetherLength);
	}

	void increaseTetherLength(float dt)
	{
		tetherLength += 20 * dt;
		std::cout << tetherLength << endl;
		joint->SetLength(tetherLength);
	}

	virtual ~HookComponent()
	{
		PhysicsSystem::World().DestroyJoint(joint);
		delete pivot;
		delete line;
	}

	b2DistanceJoint* joint;
	CollisionBoxComponent* pivot;
	LineComponent* line;
	float tetherLength;
};
