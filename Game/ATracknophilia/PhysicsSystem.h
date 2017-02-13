#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"



class PhysicsSystem : public ISystem
{
public:
	void process(float dt) override
	{
		World().Step(dt, 6, 3);
	}

	static b2Vec2& Gravity()
	{
		static b2Vec2 gravity(0, 50);
		return gravity;
	}

	static b2World& World()
	{
		static b2World world(Gravity());
		world.SetGravity(Gravity());
		return world;
	}
private:

};
