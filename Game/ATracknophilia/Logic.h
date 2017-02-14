#pragma once
#include "ECSInterfaces.h"
#include <functional>
#include "Dimensional.h"

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