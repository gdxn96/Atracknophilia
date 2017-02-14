#pragma once
#include "ECSInterfaces.h"

struct DirectionComponent : public IComponent, public AutoLister<DirectionComponent>
{
	DirectionComponent(int id, Vector2D direction)
		: IComponent(id)
		, m_direction(direction)
	{
	}

	Vector2D m_direction;
};