#pragma once
#include "ECSInterfaces.h"
#include "Components.h"

class StateSystem : public ISystem
{
public:
	StateSystem() {};

	void process(float dt) override
	{
		auto& components = AutoList::get<StateComponent>();
		for (auto& component : components)
		{
			using namespace ANIMATIONS::PLAYER;

			auto p = component->getParent();
			if (component->state->getType() == "idle")
			{
				if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x > 0)
				{
					//move right
					component->getComponent<AnimationComponent>()->animation.changeAnimation(BLUE::RUNNINGRIGHT);
					component->state = new Running(false);
				}
				else if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x < 0)
				{
					//run left
					component->getComponent<AnimationComponent>()->animation.changeAnimation(BLUE::RUNNINGLEFT);
					component->state = new Running(true);
				}
				//else if () //Button press for jump
				//{

				//}
				//else if () //button press for shoot
				//{

				//}
				//else if () //check for hit
				//{

				//}
			}
			else if (component->state->getType() == "running")
			{
				if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x == 0)
				{
					component->getComponent<AnimationComponent>()->animation.changeAnimation(BLUE::FALLRIGHT);
					component->state = new Idle(component->state->getDirection());
				}
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
