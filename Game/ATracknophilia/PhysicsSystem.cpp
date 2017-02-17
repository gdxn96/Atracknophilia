#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Logic.h"
#include "Property.h"

void PhysicsSystem::process(float dt)
{
	auto& components = AutoList::get<PhysicsLogicComponent>();
	for (auto& component : components)
	{
		component->execute();
	}
	World().Step(dt, 7, 3);


	auto& boxComponents = AutoList::get<Box2DComponent>();
	for (auto& c : boxComponents)
	{
		auto maxVel = getComponentById<MaxVelocityComponent>(c->ID);
		b2Vec2 vel = c->body->GetLinearVelocity();
		float32 speed = vel.Length();
		if (maxVel != nullptr && speed > maxVel->m_maxVelocity)
			c->body->SetLinearVelocity((maxVel->m_maxVelocity / speed) * vel);
	}
}

Vector2D PhysicsSystem::RayCast(Vector2D start, Vector2D end, float maxLength)
{
	b2RayCastInput input;
	input.p1 = start.toBox2DVector();
	input.p2 = end.toBox2DVector();
	input.maxFraction = 1;

	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2
	b2Vec2 intersectionNormal(0, 0);
	for (b2Body* b = World().GetBodyList(); b; b = b->GetNext()) {
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput output;
			if (!f->RayCast(&output, input, 0))
				continue;
			if (output.fraction < closestFraction) {
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}
		}
	}

	Vector2D intersectionPoint = start + (end - start) * closestFraction;
	return intersectionPoint;
}

b2Vec2 & PhysicsSystem::Gravity()
{
	static b2Vec2 gravity(0, 100);
	return gravity;
}

b2World & PhysicsSystem::World()
{
	static b2World world(Gravity());
	world.SetGravity(Gravity());
	return world;
}
