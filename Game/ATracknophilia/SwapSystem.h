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

				float dis = Vector2D::Distance(Vector2D(collider->body->GetPosition()), Vector2D(swap->target->GetPosition()));
				std::cout << "Distance: " << dis << " Length: " << swap->tetherLength << std::endl;
				if (swap->isShot)
				{
					swap->isShot = false;
				}
				else if (dis >= swap->tetherLength - 2)
				{
					std::cout << "Destroyed => Distance: " << dis << " Length: " << swap->tetherLength << std::endl;
					collider->getParent()->deleteComponent<SwapComponent>();
				}
			}
		}
	}
private:

};
