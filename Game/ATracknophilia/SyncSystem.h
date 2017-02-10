#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"

class SyncSystem : public ISystem
{
public:
	SyncSystem()
	{
	}

	void process() override
	{
		auto& components = AutoList::get<Box2DComponent>();
		for (auto& component : components)
		{
			component->process();
		}
	}

private:

};