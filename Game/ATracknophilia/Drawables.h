#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"
#include "Vector2D.h"


struct LineComponent : public IComponent, AutoLister<LineComponent>
{
	LineComponent(int id, Vector2D _start, Vector2D _end) 
		:	IComponent(id)
		,	start(_start)
		,	end(_end) 
	{};
	Vector2D start, end;
};