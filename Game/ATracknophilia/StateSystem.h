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

			int id = p->getComponent<AnimationComponent>()->coulourID;

			//IDLING
			if (component->state->getType() == "idle"){
				if (runCheck(component, id)) {} //run
				else if (swingCheck(component, id)) {} //swing
				else if (fallCheck(component, id)) {} //fall
			}

			//RUNNING
			else if (component->state->getType() == "running"){
				if (idleCheck(component, id)) {}
				else if (swingCheck(component, id)) {} //swing
				else if (fallCheck(component, id)) {} //fall
				else if (runCheck(component, id)) {}
			}
			//SWINGING
			else if (component->state->getType() == "swinging"){
				if (!p->getComponent<HookComponent>()) //check if hooks exists, cannot leave swing untill not on a hook
				{
					if (fallCheck(component, id)) {} //fall
					if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().y == 0)
					{
						runCheck(component, id);
					}
					else
					{
						component->state = new Idle(component->state->getDirection());
					}
				}
			}
			//FALLING
			else if (component->state->getType() == "falling"){
				if (swingCheck(component, id)) {} //swing
				else if (idleCheck(component, id)) {}
				else if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().y == 0)
				{
					runCheck(component, id);
				}
			}
			//LANDING
			else if (component->state->getType() == "landing")
			{

			}
			//ATTACKING
			else if (component->state->getType() == "attacking")
			{

			}
			//HITTING
			else if (component->state->getType() == "hitting")
			{

			}
		}

	}
	//Colour 0 = Blue, 1 = Green, 2 = Red, 3 = Yellow
	bool idleCheck(StateComponent* component, int colour)
	{
		auto p = component->getParent();
		if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity() == b2Vec2(0,0))
		{
			if (!component->state->getDirection())
			{
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::IDLERIGHT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::IDLERIGHT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::IDLERIGHT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::IDLERIGHT);
					break;
				}
			}
			else
			{
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::IDLELEFT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::IDLELEFT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::IDLELEFT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::IDLELEFT);
					break;
				}
			}
			component->state = new Idle(component->state->getDirection());
			return true;
		}
		return false;
	}
	bool runCheck(StateComponent* component, int colour)
	{
		auto p = component->getParent();
		if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x > 0) //runright
		{
			//move right
			switch (colour)
			{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::RUNNINGRIGHT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::RUNNINGRIGHT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::RUNNINGRIGHT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::RUNNINGRIGHT);
					break;
			}
			
			component->state = new Running(false);
			return true;
		}
		else if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x < 0) //runleft
		{
			//run left
			//move right
			switch (colour)
			{
			case 0:
				component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::RUNNINGLEFT);
				break;
			case 1:
				component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::RUNNINGLEFT);
				break;
			case 2:
				component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::RUNNINGLEFT);
				break;
			case 3:
				component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::RUNNINGLEFT);
				break;
			}
			component->state = new Running(true);
			return true;
		}

		return false;
	}
	bool swingCheck(StateComponent* component, int colour)
	{
		auto p = component->getParent();
		if (p->getComponent<HookComponent>())  //check if hooks exists, cannot enter swing until on a hook
		{
			if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x >= 0)
			{
				//move right
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::SWINGRIGHT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::SWINGRIGHT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::SWINGRIGHT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::SWINGRIGHT);
					break;
				}
				component->state = new Swinging(false);
			}
			else
			{
				//move right
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::SWINGLEFT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::SWINGLEFT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::SWINGLEFT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::SWINGLEFT);
					break;
				}
				component->state = new Swinging(true);
			}
			return true;
		}


		return false;
	}
	bool fallCheck(StateComponent* component, int colour)
	{
		auto p = component->getParent();
		if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().y > 0)
		{
			if (p->getComponent<DynamicBodyComponent>()->body->GetLinearVelocity().x >= 0)
			{
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::FALLRIGHT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::FALLRIGHT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::FALLRIGHT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::FALLRIGHT);
					break;
				}
				component->state = new Falling(false);
				return true;
			}
			else
			{
				switch (colour)
				{
				case 0:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::BLUE::FALLLEFT);
					break;
				case 1:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::GREEN::FALLLEFT);
					break;
				case 2:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::RED::FALLLEFT);
					break;
				case 3:
					component->getComponent<AnimationComponent>()->animation.changeAnimation(ANIMATIONS::PLAYER::YELLOW::FALLLEFT);
					break;
				}
				component->state = new Falling(true);
				return true;
			}
		}	
		return false;
	}

private:
};
