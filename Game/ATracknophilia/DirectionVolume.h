#pragma once
#include "Components.h"

class DirectionVolume : public IEntity, public AutoLister<DirectionVolume>
{
public:
	DirectionVolume(int id, float x, float y, float w, float h, int priority, Vector2D direction)
		: IEntity(id,{	
						new SoftObstacleComponent(id, x, y, w, h, true, true),
						new PlayerCollisionResponseComponent(id),
						new PriorityComponent(id, priority), 
						new DirectionComponent(id, direction),
					})
	{
	}
private:

};
