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
private:

};


