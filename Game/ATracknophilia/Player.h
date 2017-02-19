#pragma once
#include "Components.h"

class Player : public IEntity, public AutoLister<Player>
{
public:
	Player(int id, float x, float y, float w, float h, int controllerId) 
		:	IEntity(id, 
			{ 
				new CollisionBoxComponent(id, x, y, w, h, false),
				new StaminaComponent(id, 100),
				new MaxAccelerationComponent(id, 20),
				new MaxVelocityComponent(id, 50),
				new PlayerControllerComponent(id, controllerId),
				new BoostComponent(id),
				new RacePositionComponent(id),
			})
	{
	}
private:

};

