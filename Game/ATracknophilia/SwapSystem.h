#pragma once
#include "ECSInterfaces.h"
#include "Interactables.h"
#include "Dimensional.h"

class SwapSystem : public ISystem
{
public:
	void process(float dt) override
	{
		auto components = AutoList::get<SwapComponent>();
		for (auto swap : components)
		{
			auto collider = swap->getComponent<Box2DComponent>();
			if (collider)
			{
				swap->line->start = collider->body->GetPosition();
			}
		}
	}
private:

};
