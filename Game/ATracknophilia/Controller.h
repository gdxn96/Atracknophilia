#pragma once
#include "ECSInterfaces.h"
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
		InputManager::GetInstance()->AddListener(BUTTON_A, this);
	}

	void process() override
	{
		InputManager::GetInstance()->GetLeftStickVector();
	}

	virtual void onEvent(Event evt) override
	{
		switch (evt)
		{
		case BUTTON_A:
			//swap gravity or something?
			break;
		default:
			break;
		}
	}
};