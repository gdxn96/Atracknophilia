#pragma once
#include "ECSInterfaces.h"
#include <functional>
#include "Dimensional.h"
#include "DirectionVolume.h"
#include "Player.h"

struct LogicComponent : public IComponent
{
public:
	LogicComponent(int id, std::function<void()> fn) : IComponent(id), m_function(fn) {};
	void execute()
	{
		m_function();
	}
	virtual ~LogicComponent() {};
private:
	std::function<void()> m_function;
};

struct CollisionResponseComponent : public AutoLister<CollisionResponseComponent>, public IComponent
{
	CollisionResponseComponent(int id)
		: IComponent(id)
	{

	}

	virtual void endContact(IEntity* e)
	{

	};

	virtual void beginContact(IEntity* e)
	{

	};
};

struct PlayerCollisionResponseComponent : CollisionResponseComponent
{
	PlayerCollisionResponseComponent(int id)
		: CollisionResponseComponent(id)
	{

	}

	void endContact(IEntity* e)
	{

	};

	void beginContact(IEntity* e)
	{

	};
};

struct DirectionVolumeCollisionResponseComponent : CollisionResponseComponent
{
	DirectionVolumeCollisionResponseComponent(int id)
		: CollisionResponseComponent(id)
	{

	}

	void endContact(IEntity* e)
	{

	};

	void beginContact(IEntity* e)
	{
		int volumeID = this->ID;
		auto racePositionComponent = e->getComponent<RacePositionComponent>();
		
		if (racePositionComponent)
		{
			racePositionComponent->SetVolumeId(volumeID);
		}
	};
};