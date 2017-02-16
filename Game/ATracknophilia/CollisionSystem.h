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
		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->beginContact(boxComponent->getParent());
			}
		}

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->beginContact(boxComponent->getParent());
			}
		}
	}

	void EndContact(b2Contact * contact)
	{
		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->endContact(boxComponent->getParent());
			}
		}

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->endContact(boxComponent->getParent());
			}
		}
	}
private:

};
