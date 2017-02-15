#pragma once
#include "Components.h"

class Player : public IEntity, public AutoLister<Player>
{
public:
	Player(int id, float x, float y, float w, float h) 
		:	IEntity(id, 
			{ 
				new CollisionBoxComponent(id, x, y, w, h, false),	
				new PlayerControllerComponent(id),
				new InvertGravityOnEdgeComponent(id),
				new RacePositionComponent(id, 0, 0),
			})
	{
	}
private:

};

