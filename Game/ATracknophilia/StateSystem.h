#pragma once
#include "ECSInterfaces.h"
#include "Drawables.h"

class StateSystem : public ISystem
{
public:
	StateSystem() {};

	void process(float dt) override
	{
		auto& components = AutoList::get<StateComponent>();
		for (auto& component : components)
		{
			auto p = component->getParent();
			if (component->state == new Idle())
			{

			}
			else if (component->state == new Running())
			{

			}
			else if (component->state == new Jumping())
			{

			}
			else if (component->state == new Falling())
			{

			}
			else if (component->state == new Landing())
			{

			}
			else if (component->state == new Attacking())
			{

			}
			else if (component->state == new Hitting())
			{

			}
		}

	}

private:
};
