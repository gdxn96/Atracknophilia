#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"

class Player : public IEntity
{
public:
	Player(int id) 
		: IEntity(id, 
		{
			new PositionComponent(id, Vector2D(100, 100)),
			new SizeComponent(id, Vector2D(50, 50)),
			new CollisionBoxComponent(id, 50, 50, 500, 500, false),		
		})
	{
	}

private:

};

