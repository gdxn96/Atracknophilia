#pragma once
#include "Components.h"

class Player : public IEntity
{
public:
	Player(int id, float x, float y, float w, float h) 
		:	IEntity(id, 
			{ 
				new DynamicBodyComponent(id, x, y, w, h, false),	
				new PlayerControllerComponent(id),
				new InvertGravityOnEdgeComponent(id), 
				new PlayerCollisionResponseComponent(id)
			})
	{
	}
private:

};

