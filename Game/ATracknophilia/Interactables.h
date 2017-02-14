#pragma once
#include "ECSInterfaces.h"
#include "Vector2D.h"

struct HookComponent : public IComponent
{
	HookComponent(int id) 
		:	IComponent(id)
	{
	}
	Vector2D pivotPoint;
	bool active;
};
