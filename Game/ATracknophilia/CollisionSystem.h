#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"
#include "Logic.h"

class CollisionSystem : public ISystem, public b2ContactListener
{
public:
	void process(float dt) override
	{

	}

	CollisionSystem()
	{
		PhysicsSystem::World().SetContactListener(this);
	}

	void BeginContact(b2Contact * contact)
	{
		void * bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void * bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB)
		{
			auto boxComponentA = static_cast<Box2DComponent*>(bodyUserDataA);
			auto collisionResponseA = boxComponentA->getComponent<CollisionResponseComponent>();

			auto boxComponentB = static_cast<Box2DComponent*>(bodyUserDataB);
			auto collisionResponseB = boxComponentB->getComponent<CollisionResponseComponent>();

			if (collisionResponseA)
			{
				collisionResponseA->beginContact(boxComponentB->getParent());
			}
			if (collisionResponseB)
			{
				collisionResponseB->beginContact(boxComponentA->getParent());
			}
		}
	}

	void EndContact(b2Contact * contact)
	{
		void * bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void * bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB)
		{
			auto boxComponentA = static_cast<Box2DComponent*>(bodyUserDataA);
			auto collisionResponseA = boxComponentA->getComponent<CollisionResponseComponent>();

			auto boxComponentB = static_cast<Box2DComponent*>(bodyUserDataB);
			auto collisionResponseB = boxComponentB->getComponent<CollisionResponseComponent>();

			if (collisionResponseA)
			{
				collisionResponseA->endContact(boxComponentB->getParent());
			}
			if (collisionResponseB)
			{
				collisionResponseB->endContact(boxComponentA->getParent());
			}
		}
	}
private:

};