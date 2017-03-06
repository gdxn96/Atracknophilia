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
			else if (getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->timeToRun > 0)
			{
				float t = getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->timeToRun;
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->timeToRun -= dt;
			}
			else
			{
				getComponentById<Player>(component->ID)->getComponent<InputPauseComponent>()->isPaused = false;
			}
		}
	}

private:
};
