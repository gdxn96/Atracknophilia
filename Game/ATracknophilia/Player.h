#pragma once
#include "Components.h"

class Player : public IEntity
{
public:
	Player(int id, float x, float y, float w, float h) 
		:	IEntity(id, 
			{ 
				new CollisionBoxComponent(id, x, y, w, h, false),
				new StaminaComponent(id, 100),
				new MaxAccelerationComponent(id, 100),
				new MaxVelocityComponent(id, 50),
				new PlayerControllerComponent(id),
				new InvertGravityOnEdgeComponent(id),
				new BoostComponent(id)
			})
	{
	}
private:

};

