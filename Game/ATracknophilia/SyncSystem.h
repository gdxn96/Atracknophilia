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
		for (auto& component : AutoList::get<Box2DComponent>())
		{
			component->process();
		}
	}

private:

};