#pragma once
//#include "ECSInterfaces.h"
#include "PowerUp.h"
#include "Logic.h"

class PowerUpSystem : public ISystem
{
public:
	PowerUpSystem()
	{}

	void process(float dt) override
	{
		for (auto& component : AutoList::get<PowerUp>())
		{
			auto r = component->getComponent<PowerUpRespawnComponent>();
			if (r && r->isDead)
			{
				r->tts += dt;
				if (r->tts >= 10)
				{
					r->ReSpawn();
				}
			}
		}
	}
};