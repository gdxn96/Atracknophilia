#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"
#include "Animation.h"

struct AnimationComponent : public IComponent, public AutoLister<AnimationComponent>
{
	AnimationComponent(int objectId, string animationName)
		: IComponent(objectId)
		, animation(Animation(animationName)) {};
	Animation animation;
};