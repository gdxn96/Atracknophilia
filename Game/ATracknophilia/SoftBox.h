#pragma once
#include "Components.h"

class SoftBox : public IEntity
{
public:
	SoftBox(int id, float x, float y, float w, float h) : IEntity(id,
	{
		new SensorComponent(id, x, y, w, h),
		//new PlayerCollisionResponseComponent(id),
	})
	{

	}

private:

};