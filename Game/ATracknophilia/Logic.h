#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"

struct CollisionResponseComponent : public AutoLister<CollisionResponseComponent>, public IComponent
{
	CollisionResponseComponent(int id)
		: IComponent(id)
	{

	}

	virtual void endContact() 
	{
	
	};

	virtual void beginContact() 
	{

	};
};

struct PlayerCollisionResponseComponent : CollisionResponseComponent
{
	PlayerCollisionResponseComponent(int id)
		: CollisionResponseComponent(id)
	{

	}

	void endContact()
	{

	};

	void beginContact()
	{
		auto box2dcomp = getComponent<Box2DComponent>();

		box2dcomp->body->SetLinearVelocity(-box2dcomp->body->GetLinearVelocity());
	};
};