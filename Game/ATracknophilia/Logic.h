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

	};
};