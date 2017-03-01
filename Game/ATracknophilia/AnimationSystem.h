#pragma once
#include "ECSInterfaces.h"
#include "Drawables.h"

class AnimationSystem : public ISystem
{
public:
	AnimationSystem() {};

	void process(float dt) override
	{
		auto& components = AutoList::get<AnimationComponent>();
		for (auto& component : components)
		{
			component->animation.m_timeSinceLastFrame += dt;
			if (component->animation.m_timeSinceLastFrame > component->animation.FPS && component->animation.m_isAlive)
			{
				if (component->animation.m_frameIndex < component->animation.m_currentFrames.size() - 1)
				{
					//increment frame
					component->animation.m_frameIndex++;
					component->animation.m_currentFrame = component->animation.m_currentFrames.at(component->animation.m_frameIndex);
				}
				else
				{
					if (!component->animation.m_isLooping)
					{
						component->animation.m_isAlive = false;
					}
					else
					{
						component->animation.m_frameIndex = 0;
						component->animation.m_currentFrame = component->animation.m_currentFrames.at(component->animation.m_frameIndex);
					}
				}

				component->animation.m_timeSinceLastFrame = 0;
			}


			//component->getParent()->getComponent<StateComponent>()->state->update(dt);
		}
	}




private:

};
