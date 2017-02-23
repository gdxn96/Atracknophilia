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
		for (auto& swap : components)
		{
			auto collider = swap->getComponent<Box2DComponent>();
			if (collider)
			{
				swap->line->start = collider->body->GetPosition();
				swap->line->end = swap->target->GetPosition();

				float dis = (collider->body->GetPosition() - swap->target->GetPosition()).Normalize();
				if (swap->isShot)
				{
					swap->isShot = false;
				}
				else if (dis >= swap->tetherLength || dis <= -swap->tetherLength)
				{
					collider->getParent()->deleteComponent<SwapComponent>();
				}
			}
		}
	}
private:

};
