#pragma once
#include "ECSInterfaces.h"

class GameplaySystem : public ISystem
{
public:
	GameplaySystem()
	{
	}

	void process(float dt) override
	{
		for (auto& component : AutoList::get<ScoreComponent>())
		{

		}
	}

private:

};
