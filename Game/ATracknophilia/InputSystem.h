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
			if (!getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->isPaused || !getComponentById<Player>(component->ID)->getComponent<ScoreComponent>()->alive)
			{
				component->process(dt);
			}	
			else if (getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->startTime == 0)
			{
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->startTime = SDL_GetTicks();
			}
			else if (SDL_GetTicks() - getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->startTime > getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->timeToPause)
			{
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->isPaused = false;
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->startTime = 0;
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->timeToPause = 0;
			}
		}
	}

private:

};
