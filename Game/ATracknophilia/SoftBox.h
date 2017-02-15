#pragma once
#include "Components.h"

class SoftBox : public IEntity
{
public:
	SoftBox(int id, float x, float y, float w, float h) 
		:	IEntity(id,
			{
				new SoftObstacleComponent(id, x, y, w, h, true, true),
				new SoftObstacleResponseComponent(id)
			})
	{
	}
private:

};