#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"
#include "FLInput\FLInputManager.h"

struct IControllerComponent : public IComponent, public AutoLister<IControllerComponent>, public EventListener
{
	IControllerComponent(int id) : IComponent(id)
	{

	}

	virtual void process() = 0;
};

struct PlayerControllerComponent : public IControllerComponent
{
	PlayerControllerComponent(int id) : IControllerComponent(id)
	{
		InputManager::GetInstance()->AddListener(ARROW_LEFT, this);
		InputManager::GetInstance()->AddListener(ARROW_RIGHT, this);
	}

	void process() override
	{
		InputManager::GetInstance()->GetLeftStickVector();
	}

	virtual void onEvent(Event evt) override
	{
		auto c = getComponent<CollisionBoxComponent>();
		if (!c) { return; }
		switch (evt)
		{
		case ARROW_LEFT:
			//example
			c->body->SetLinearVelocity(b2Vec2(-1000, 0));
			break;
		case ARROW_RIGHT:
			//example
			c->body->SetLinearVelocity(b2Vec2(1000, 0));
			break;
		default:
			break;
		}
	}
};