#pragma once
#include "Node.h"

class Leaf : public Node
{
public:
	virtual ~Leaf() {}
};

class UseAbility : public Leaf
{
public:
	UseAbility() {}
	~UseAbility() {}

	Status Update(IEntity* p)
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
		//			break;
		//		}
		// }
		std::cout << "use ability failed" << std::endl;
		return Status::Failure;
	}
};

class MoveInDirectionOfVolume : public Leaf
{
public:
	MoveInDirectionOfVolume() {}
	~MoveInDirectionOfVolume() {}

	Status Update(IEntity* p)
	{
		auto b = p->getComponent<Box2DComponent>();
		auto a = p->getComponent<MaxAccelerationComponent>();
		auto rp = p->getComponent<RacePositionComponent>();

		if (a && b && rp)
		{
			auto dirVol = getComponentById<DirectionVolume>(rp->volumeID);
			if (dirVol)
			{
				auto dirComp = dirVol->getComponent<DirectionComponent>();
				if (dirComp)
				{
					auto direction = dirComp->m_direction;
					auto obstacle = PhysicsSystem::RayCastToStaticObject(b->body->GetPosition(), Vector2D(b->body->GetPosition()) + Vector2D(direction.x * 1000, direction.y * 1000));
					if (obstacle.first)
					{
						float distance = Vector2D::Distance(Vector2D(b->body->GetPosition()), obstacle.second);
						if (distance < 5)
						{
							std::cout << "obstacle too close" << std::endl;
							return Status::Failure;
						}
						b->body->ApplyForceToCenter(b2Vec2(direction.x * a->m_maxAcceleration, direction.y * a->m_maxAcceleration), true);
						std::cout << "moving in direction of volume" << std::endl;
						return Status::Running;
					}
				}
			}
		}
		std::cout << "move in direction of volume failed" << std::endl;
		return Status::Failure;
	}
};

class MoveInXDirection : public Leaf
{
public:
	MoveInXDirection() {}
	~MoveInXDirection() {}

	Status Update(IEntity* p)
	{
		auto b = p->getComponent<Box2DComponent>();
		auto a = p->getComponent<MaxAccelerationComponent>();
		auto rp = p->getComponent<RacePositionComponent>();

		if (a && b && rp)
		{
			auto dirVol = getComponentById<DirectionVolume>(rp->volumeID);
			if (dirVol)
			{
				auto dirComp = dirVol->getComponent<DirectionComponent>();
				if (dirComp)
				{
					auto direction = dirComp->m_direction;
					int dirX = 0;
					if (direction.x > 0)
					{
						dirX = 1;
					}
					else
					{
						dirX = -1;
					}
					auto obstacle = PhysicsSystem::RayCastToStaticObject(b->body->GetPosition(), Vector2D(b->body->GetPosition()) + Vector2D(dirX * 1000, 0));
					if (obstacle.first)
					{
						float distance = Vector2D::Distance(Vector2D(b->body->GetPosition()), obstacle.second);
						if (distance < 5)
						{
							std::cout << "obstacle too close" << std::endl;
							return Status::Failure;
						}
						b->body->ApplyForceToCenter(b2Vec2(dirX * a->m_maxAcceleration, 0), true);
						std::cout << "moving in X direction" << std::endl;
						return Status::Running;
					}
				}
			}
		}
		std::cout << "move in x direction failed" << std::endl;
		return Status::Failure;
	}
};

class UseHook : public Leaf
{
public:
	UseHook() {}
	~UseHook() {}

	Status Update(IEntity* p)
	{
		auto b = p->getComponent<Box2DComponent>();
		auto h = p->getComponent<HookComponent>();
		if (!h && b)
		{
			float xVelocity = b->body->GetLinearVelocity().x;
			float xRay = 0;
			if (xVelocity > 0) { xRay = 1000; }
			else if (xVelocity < 0) { xRay = -1000; }
			auto intersection = PhysicsSystem::RayCastToStaticObject(b->body->GetPosition(), Vector2D(b->body->GetPosition()) + Vector2D(xRay, -1000));
			if (intersection.first)
			{
				auto isStatic = intersection.first->getComponent<StaticBodyComponent>();
				float distance = Vector2D::Distance(Vector2D(b->body->GetPosition()), intersection.second);
				if (distance > 5 && isStatic)
				{
					p->AddComponent(new HookComponent(p->ID, b->body->GetPosition(), intersection.second, b->body));
					std::cout << "hook created" << std::endl;
					return Status::Success;
				}
			}
		}
		//std::cout << "use hook failed" << std::endl;
		return Status::Success;
	}
};

class RaiseHook : public Leaf
{
public:
	RaiseHook() {}
	~RaiseHook() {}

	Status Update(IEntity* p)
	{
		auto h = p->getComponent<HookComponent>();
		// get y value of direction volume and move up and down accordingly
		if (h)
		{
			if (h->tetherLength < 5)
			{
				std::cout << "tether removed" << std::endl;
				h->getParent()->deleteComponent<HookComponent>();
				return Status::Success;
			}
			else
			{
				h->decreaseTetherLength(0.01);
				std::cout << "tether decreasing" << std::endl;
				return Status::Success;
			}
		}
		std::cout << "raise hook failed" << std::endl;
		return Status::Failure;
	}
};

class ActivateStamina : public Leaf
{
public:
	ActivateStamina() {}
	~ActivateStamina() {}

	Status Update(IEntity* p)
	{
		return Status::Failure;
	}
};

class CheckHooked : public Leaf
{
public:
	CheckHooked() {}
	~CheckHooked() {}

	Status Update(IEntity* p)
	{
		auto h = p->getComponent<HookComponent>();
		if (h)
		{
			std::cout << "has hook" << std::endl;
			return Status::Success;
		}
		std::cout << "no hook" << std::endl;
		return Status::Failure;
	}
};