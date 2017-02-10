#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"

class Player : public IEntity
{
public:
	Player(int id) 
		: IEntity(id, 
		{
			new CollisionBoxComponent(id, 50, 50, 50, 50, false),	
			new PlayerControllerComponent(id),
		})
	{
	}

private:

};

