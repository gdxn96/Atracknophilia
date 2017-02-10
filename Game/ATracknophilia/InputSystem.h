#pragma once
#include "ECSInterfaces.h"
#include "Controller.h"

class InputSystem : public ISystem
{
public:
	InputSystem()
	{
	}

	void process() override
	{
		for (auto& component : AutoList::get<IControllerComponent>())
		{
			component->process();
		}
	}

private:

};
