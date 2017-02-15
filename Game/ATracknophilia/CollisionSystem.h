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
				collisionRespone->beginContact();
			}
		}

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->beginContact();
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
				collisionRespone->endContact();
			}
		}

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			auto boxComponent = static_cast<CollisionBoxComponent*>(bodyUserData);
			auto collisionRespone = boxComponent->getComponent<CollisionResponseComponent>();
			if (collisionRespone)
			{
				collisionRespone->endContact();
			}
		}
	}
private:

};
