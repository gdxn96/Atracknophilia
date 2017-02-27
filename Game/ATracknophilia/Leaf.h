#pragma once
#include "Node.h"
#include "Entities.h"
#include <vector>
#include <memory>

class Leaf : public Node
{
public:
	Leaf() {}
	virtual ~Leaf() {}
	Leaf(AIPlayer* p) : player(p) {}

	void SetPlayer(AIPlayer* p) { player = p; }

	virtual Status Update() = 0;

protected:
	AIPlayer* player;
};

class isObstructed : public Leaf
{
public:
	isObstructed() {}
	~isObstructed() {}
	isObstructed(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		auto c = player->getComponent<Box2DComponent>();
		if (c)
		{
			float xVelocity = c->body->GetLinearVelocity().x;
			float xRay = 0;
			if (xVelocity > 0) { xRay = 1000; }
			else if (xVelocity < 0) { xRay = -1000; }
			auto intersection = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
			if (intersection.first)
			{
				auto isStatic = intersection.first->getComponent<StaticBodyComponent>();
				float distance = Vector2D::Distance(Vector2D(c->body->GetPosition()), intersection.second);
				if (distance > 10 && isStatic)
				{
					return Status::Success;
				}
			}
		}
		return Status::Failure;
	}
};

class UseHook : public Leaf
{
public:
	UseHook() {}
	~UseHook() {}
	UseHook(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		auto c = player->getComponent<Box2DComponent>();
		auto h = player->getComponent<HookComponent>();
		if (!h && c)
		{
			float xVelocity = c->body->GetLinearVelocity().x;
			float xRay = 0;
			if (xVelocity > 0) { xRay = 1000; }
			else if (xVelocity < 0) { xRay = -1000; }
			auto intersection = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
			player->AddComponent(new HookComponent(player->ID, c->body->GetPosition(), intersection.second, c->body));
			return Status::Success;
		}
		return Status::Failure;
	}
};

class RaiseHook : public Leaf
{
public:
	RaiseHook() {}
	~RaiseHook() {}
	RaiseHook(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		auto h = player->getComponent<HookComponent>();
		if (h)
		{
			// if (h->tetherLength > someDistance)
			// {
			//		return Status::Success
			// }
			// else
			// {
			//		h->decreaseTetherLength(dt);
			//		return Status::Running;
			// }
		}
		return Status::Failure;
	}
};


class UseAbility : public Leaf
{
public:
	UseAbility() {}
	~UseAbility() {}
	UseAbility(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		// auto a = player->getComponent<AbilityComponent>();
		// auto c = player->getComponent<Box2DComponent>();
		// if(a && c)
		// {
		//		switch(a->ability)
		//		{
		//		case WEB_DROP:
		//			EntityFactory::SpawnWebDrop(c->body->GetPosition().x, c->body->GetPosition().y, 1, 1);
		//			a->ability = NONE;
		//			return Status::Success;
		//		case SLOW_SHOT:
		//			EntityFactory::SpawnSlowShot(c->body->GetPosition().x, c->body->GetPosition().y - 1, 1, 1, player->ID);
		//			a->ability = NONE;
		//			return Status::Success;
		//		case SWAP_SHOT;
		//			do swap shot stuff....
		//			a->ability = NONE;
		//			return Status::Success;
		//		case default:
		//			a->ability = NONE;
		//			return Status::Failure;
		//		}
		// }
		return Status::Failure;
	}

};

class MoveLeft : public Leaf
{
public:
	MoveLeft() {}
	~MoveLeft() {}
	MoveLeft(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		auto c = player->getComponent<Box2DComponent>();
		if (c)
		{
			float xVelocity = c->body->GetLinearVelocity().x;
			float xRay = -1000;
			auto obstacle = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
			float distance = Vector2D::Distance(Vector2D(c->body->GetPosition()), obstacle.second);
			if (distance > 10 && !obstacle.first)
			{
				c->body->ApplyForceToCenter(b2Vec2(-5, 0), true);
				return Status::Running;
			}
			else
			{
				return Status::Success;
			}
		}

		return Status::Failure;
	}

};

class MoveRight : public Leaf
{
public:
	MoveRight() {}
	~MoveRight() {}
	MoveRight(AIPlayer* p) : Leaf(p) {}

	Status Update()
	{
		auto c = player->getComponent<Box2DComponent>();
		if (c)
		{
			float xVelocity = c->body->GetLinearVelocity().x;
			float xRay = 1000;
			auto obstacle = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
			float distance = Vector2D::Distance(Vector2D(c->body->GetPosition()), obstacle.second);
			if (distance > 10 && !obstacle.first)
			{
				c->body->ApplyForceToCenter(b2Vec2(5, 0), true);
				return Status::Running;
			}
			else
			{
				return Status::Success;
			}
		}

		return Status::Failure;
	}

};
