#pragma once
#include "ECSInterfaces.h"
#include "Controller.h"

class InputSystem : public ISystem
{
public:
	InputSystem()
	{
	}

	void process(float dt) override
	{
		for (auto& component : AutoList::get<IControllerComponent>())
		{
			if (!getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->isPaused)
			{
				component->process(dt);
			}	
			else if (getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->time == 0)
			{
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->time = SDL_GetTicks();
			}
			else if (SDL_GetTicks() - getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->time > 3000)
			{
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->isPaused = false;
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->time = 0;
			}
		}
	}

private:

};
