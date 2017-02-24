#pragma once
#include "Components.h"
#include "Logic.h"

class ICollisionResponseComponent;
struct PlayerStaticObjectResponseComponent : public ICollisionResponseComponent
{
	PlayerStaticObjectResponseComponent(int id)
		: ICollisionResponseComponent(id)
	{

	}

	void endContact(IEntity * e)
	{

	};

	void beginContact(IEntity * e)
	{
		if (e)
		{
			auto isStaticObject = e->getComponent<StaticBodyComponent>();
			if (isStaticObject)
			{
				auto hook = getComponent<HookComponent>();
				if (hook)
				{
					hook->alive = false;
				}
				return;
			}
		}
		auto collisionBody = e->getComponent <SoftObstacleResponseComponent>(); // collision with sensor component
		if (collisionBody)
		{
			auto b = getComponent<DynamicBodyComponent>();
			if (b)
				b->body->SetLinearVelocity(b2Vec2(0, 0)); // stop the player's velocity on collision
		}
	}
};

class Player : public IEntity, public AutoLister<Player>
{
public:
	Player(int id, float x, float y, float w, float h, int controllerId)
		: IEntity(id,
		{
			new DynamicBodyComponent(id, x, y, w, h, false),
			new StaminaComponent(id, 100),
			new MaxAccelerationComponent(id, 20),
			new MaxVelocityComponent(id, 50),
			new PlayerControllerComponent(id, controllerId),
			new BoostComponent(id),
			new RacePositionComponent(id),
			new PlayerStaticObjectResponseComponent(id)
		})
	{
	}
private:

};

