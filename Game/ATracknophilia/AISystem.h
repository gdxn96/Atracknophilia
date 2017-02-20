#pragma once
#include "ECSInterfaces.h"
#include "Logic.h"

class AISystem : public ISystem
{
public:
	AISystem()
	{}

	void process(float dt) override
	{
		for (auto& component : AutoList::get<AIComponent>())
		{
			component->think();
		}
	}
};