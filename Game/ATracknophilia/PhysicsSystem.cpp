#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Logic.h"

void PhysicsSystem::process(float dt)
{
	auto& components = AutoList::get<PhysicsLogicComponent>();
	for (auto& component : components)
	{
		component->execute();
	}
	World().Step(dt, 6, 3);
}

b2Vec2 & PhysicsSystem::Gravity()
{
	static b2Vec2 gravity(0, 1000);
	return gravity;
}

b2World & PhysicsSystem::World()
{
	static b2World world(Gravity());
	world.SetGravity(Gravity());
	return world;
}
