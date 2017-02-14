#pragma once
#include "ECSInterfaces.h"
#include "Controller.h"

class InputSystem : public ISystem
{
public:
	InputSystem()
	{
		InputManager::GetInstance()->SetStickDeadZone(8000);
	}

	void process(float dt) override
	{
		for (auto& component : AutoList::get<IControllerComponent>())
		{
			component->process();
		}
	}

private:

};
