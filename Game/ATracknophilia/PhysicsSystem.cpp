#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Logic.h"
#include "Property.h"

void PhysicsSystem::process(float dt)
{
	World().Step(dt, 7, 3);


	auto& boxComponents = AutoList::get<Box2DComponent>();
	for (auto& c : boxComponents)
	{
		auto maxVelComp = getComponentById<MaxVelocityComponent>(c->ID);
		auto boostComp = getComponentById<BoostComponent>(c->ID);
		auto stamComp = getComponentById<StaminaComponent>(c->ID);

		if (stamComp && stamComp->m_stamina <= 0)
		{
			// cannot boost if there is no stamina
			boostComp->m_boostActive = false;
		}

		if (boostComp && boostComp->m_boostActive)
		{
			// boost time is the time the boost button on controller is held for
			boostComp->m_boostTime += dt;
			if (stamComp->m_stamina > 0)
				stamComp->m_stamina --;
		}
		
		if (boostComp && boostComp->m_boostActive == false)
		{
			// lerp deceleration over time 
			DecelerateBoost(dt, c->ID);
		}

		// limiting the max velocity
		b2Vec2 vel = c->body->GetLinearVelocity();
		float32 speed = vel.Length();
		if (maxVelComp != nullptr && speed > maxVelComp->m_maxVelocity)
			c->body->SetLinearVelocity((maxVelComp->m_maxVelocity / speed) * vel);
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

void PhysicsSystem::DecelerateBoost(float dt, int id)
{
	auto boostComp = getComponentById<BoostComponent>(id);
	auto maxVelComp = getComponentById<MaxVelocityComponent>(id);

	boostComp->m_decelerateTime += dt;

	// while the velocity is greater than original max velocity - reduce the velocity evenly over time (lerp)
	if (maxVelComp->m_maxVelocity > boostComp->MAX_VELOCITY)
	{
		float decelPercentage = boostComp->m_decelerateTime / boostComp->m_boostTime;
		float initialValue = boostComp->BOOSTED_MAX_VELOCITY - boostComp->MAX_VELOCITY;
		float finalValue = 0;
		float decelRate = (initialValue - finalValue) * decelPercentage;
		maxVelComp->m_maxVelocity = boostComp->BOOSTED_MAX_VELOCITY - decelRate;
	}
	else
	{
		maxVelComp->m_maxVelocity = boostComp->MAX_VELOCITY;
		boostComp->m_decelerateTime = 0;
		boostComp->m_boostTime = 0;
	}
}
