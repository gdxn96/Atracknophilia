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
			new AccelerationComponent(id, 20),
			new ConstMaxAccelerationComponent(id, 20),
			new ConstBoostedAccelerationComponent(id, 150),
			new VelocityComponent(id, 50),
			new ConstMaxVelocityComponent(id, 50),
			new ConstBoostedVelocityComponent(id, 80),
			new PlayerControllerComponent(id, controllerId),
			new RacePositionComponent(id),
			new PlayerStaticObjectResponseComponent(id)
		})
	{
	}

	Player(int id, float x, float y, float w, float h, BehaviourTree* bt)
		: IEntity(id,
		{
			new DynamicBodyComponent(id, x, y, w, h, false),
			new StaminaComponent(id, 100),
			new AccelerationComponent(id, 20),
			new ConstMaxAccelerationComponent(id, 20),
			new ConstBoostedAccelerationComponent(id, 150),
			new VelocityComponent(id, 50),
			new ConstMaxVelocityComponent(id, 50),
			new ConstBoostedVelocityComponent(id, 80),
			new PlayerAIComponent(id, bt),
			new RacePositionComponent(id),
			new PlayerStaticObjectResponseComponent(id)
		})
	{
	}
private:

};

//class AIPlayer : public IEntity, public AutoLister<AIPlayer>
//{
//public:
//	AIPlayer(int id, float x, float y, float w, float h, BehaviourTree* bt)
//		: IEntity(id,
//		{
//			new DynamicBodyComponent(id, x, y, w, h, false),
//			new StaminaComponent(id, 100),
//			new AccelerationComponent(id, 20),
//			new ConstMaxAccelerationComponent(id, 20),
//			new ConstBoostedAccelerationComponent(id, 150),
//			new VelocityComponent(id, 50),
//			new ConstMaxVelocityComponent(id, 50),
//			new ConstBoostedVelocityComponent(id, 80),
//			new RacePositionComponent(id),
//			new PlayerStaticObjectResponseComponent(id),
//			new PlayerAIComponent(id, bt)
//		})
//	{
//	}
//private:
//
//};
