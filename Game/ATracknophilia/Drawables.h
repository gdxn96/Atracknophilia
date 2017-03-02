#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"
#include "Vector2D.h"
#include "Animation.h"
#include "FiniteStateMachine.h"


struct AnimationComponent : public IComponent, public AutoLister<AnimationComponent>
{
	AnimationComponent(int objectId, string animationName, int colID)
		: IComponent(objectId)
		, animation(Animation(animationName))
		, coulourID(colID){};
	Animation animation;
	int coulourID;
};

struct StateComponent : public IComponent, public AutoLister<StateComponent>
{
	StateComponent(int id)
		: IComponent(id)
		, state(new Idle(false))
		, colour("blue") {};

	IState *state;
	std::string colour;
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