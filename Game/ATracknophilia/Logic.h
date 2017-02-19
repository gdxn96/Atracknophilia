#pragma once
#include <functional>
#include "ECSInterfaces.h"
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
		auto x = getComponent<Box2DComponent>();
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

struct ICollisionResponseComponent : public AutoLister<ICollisionResponseComponent>, public IComponent
{
	ICollisionResponseComponent(int id)
		: IComponent(id)
	{

	}

	virtual void endContact(IEntity * e)
	{

	};

	virtual void beginContact(IEntity * e)
	{

	};
};

struct PlayerCollisionResponseComponent : public ICollisionResponseComponent
{
	PlayerCollisionResponseComponent(int id)
		: ICollisionResponseComponent(id)
	{

	}

	void endContact(IEntity * e)
	{

	};

	void beginContact(IEntity * e)
	{
		//getComponent<Box2DComponent>()->body->SetLinearVelocity(b2Vec2(0, 0));
	};
};

class Player;

struct SoftObstacleResponseComponent : public ICollisionResponseComponent
{
	SoftObstacleResponseComponent(int id)
		: ICollisionResponseComponent(id)
	{

	}

	void endContact(IEntity * e)
	{
	
	};

	void beginContact(IEntity * e)
	{
		auto collisionBody = e->getComponent <DynamicBodyComponent> ();
		
		if (collisionBody)
		{
			auto b = getComponent<KinematicBodyComponent>();
			if (b)
				b->body->SetLinearVelocity(b2Vec2(0, 100000));
		}
	};
};

struct AIComponent : public IComponent, public AutoLister<AIComponent>
{
	AIComponent(int id) :IComponent(id)
	{
	}

	virtual void think() {}
};

struct SeekAIComponent : public AIComponent, public AutoLister<SeekAIComponent>
{
	SeekAIComponent(int id, int target_id, int shooter_id) 
		: AIComponent(id)
		, targetID(target_id)
		, shooterID(shooter_id)
	{}

	void think()
	{
		auto target = getComponentById<Box2DComponent>(targetID);
		auto object = getComponent<Box2DComponent>();

		b2Vec2 pos = object->body->GetPosition();
		b2Vec2 targetPos = target->body->GetPosition();

		auto direction = target->body->GetPosition() - object->body->GetPosition();
		float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
		direction = b2Vec2(direction.x / length, direction.y / length);
		b2Vec2 velocity = b2Vec2(direction.x * 1000, direction.y * 1000);
		object->body->SetLinearVelocity(velocity);

		// change orienation of sprite if needed
		//if (sqrt((direction.x * direction.x) + (direction.y * direction.y)) >= 0)
		//{
		//	float orientation = atan2(direction.x, -direction.y) * (180 / 3.141592654);
		//	// set sprite rotation
		//}
	}

	int targetID;
	int shooterID;
};

struct SlowShotResponseComponent : public ICollisionResponseComponent
{
	SlowShotResponseComponent(int id)
		: ICollisionResponseComponent(id)
	{}

	void endContact(IEntity * e)
	{};

	void beginContact(IEntity * e)
	{
		auto ai = getComponent<SeekAIComponent>();
		
		if (ai && ai->shooterID != e->ID)
		{
			getParent()->alive = false;
			e->getComponent<Box2DComponent>()->body->SetLinearVelocity(b2Vec2(0, 0));
		}
	};
};