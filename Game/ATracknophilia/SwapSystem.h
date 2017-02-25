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
			swap->breakTimer += dt;

			auto collider = swap->getComponent<Box2DComponent>();
			if (collider)
			{
				auto obstacle = PhysicsSystem::RayCastToStaticObject(collider->body->GetPosition(), swap->target->getComponent<Box2DComponent>()->body->GetPosition(), 55);
				if (obstacle.first)
				{
					collider->getComponent<IControllerComponent>()->isHooked = false;
					collider->body->SetGravityScale(1);

					swap->target->getComponent<IControllerComponent>()->isHooked = false;
					swap->target->getComponent<Box2DComponent>()->body->SetGravityScale(1);
					
					collider->getParent()->deleteComponent<SwapComponent>();
				}
				else
				{
					swap->line->start = collider->body->GetPosition();
					swap->line->end = swap->target->getComponent<Box2DComponent>()->body->GetPosition();

					float dis = Vector2D::Distance(Vector2D(collider->body->GetPosition()), Vector2D(swap->target->getComponent<Box2DComponent>()->body->GetPosition()));
					if (swap->isShot)
					{
						swap->isShot = false;
					}
					else if (dis >= swap->tetherLength - 2)
					{
						collider->getComponent<IControllerComponent>()->isHooked = false;
						collider->body->SetGravityScale(1);

						swap->target->getComponent<IControllerComponent>()->isHooked = false;
						swap->target->getComponent<Box2DComponent>()->body->SetGravityScale(1);

						collider->getParent()->deleteComponent<SwapComponent>();
					}
				}
			}

			if (swap && swap->breakTimer >= 0.9f)
			{
				collider->getComponent<IControllerComponent>()->isHooked = false;
				collider->body->SetGravityScale(1);

				swap->target->getComponent<IControllerComponent>()->isHooked = false;
				swap->target->getComponent<Box2DComponent>()->body->SetGravityScale(1);

				collider->getParent()->deleteComponent<SwapComponent>();
			}
		}
	}
private:

};
