#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"
#include "Vector2D.h"
#include "Animation.h"

struct AnimationComponent : public IComponent, public AutoLister<AnimationComponent>
{
	AnimationComponent(int objectId, string animationName)
		: IComponent(objectId)
		, animation(Animation(animationName)) {};
	Animation animation;
};



struct LineComponent : public IComponent, AutoLister<LineComponent>
{
	LineComponent(int id, Vector2D _start, Vector2D _end) 
		:	IComponent(id)
		,	start(_start)
		,	end(_end) 
	{};
	Vector2D start, end;
};