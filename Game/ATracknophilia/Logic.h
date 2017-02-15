#pragma once
#include "ECSInterfaces.h"
#include <functional>
#include "Dimensional.h"
#include "Components.h"

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

struct PhysicsLogicComponent : public LogicComponent, public AutoLister<PhysicsLogicComponent>
{
public:
	PhysicsLogicComponent(int id, std::function<void()> fn) : LogicComponent(id, fn) {};
	virtual ~PhysicsLogicComponent() {};
};

//this logic allows any body to invert their gravity if they are falling upwards and reach the end of a platform
struct InvertGravityOnEdgeComponent : public PhysicsLogicComponent, public AutoLister<InvertGravityOnEdgeComponent>
{
	InvertGravityOnEdgeComponent(int id)
		:	PhysicsLogicComponent(id, std::bind(&InvertGravityOnEdgeComponent::update, this))
	{
	}

	void update()
	{
		auto x = getComponent<CollisionBoxComponent>();
		auto colliding = x->body->GetContactList();
		static b2ContactEdge* prevColliding = nullptr;
		static float prevScale = 0;

		if (!colliding && prevColliding && x->body->GetGravityScale() < 0 && prevScale == x->body->GetGravityScale())
		{
			x->body->SetGravityScale(x->body->GetGravityScale() * -1);
		}

		prevColliding = colliding;
		prevScale = x->body->GetGravityScale();
	}
};

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
		//if (getComponentById<DirectionVolume>(ID))
		//{
			//auto priority = getComponentById<PriorityComponent>(ID)->m_priority;
			//auto player = getComponent<Player>();
			//player->getComponent<RacePositionComponent>()->update(priority, ID);
		//}
	};
};