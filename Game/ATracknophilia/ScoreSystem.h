#pragma once
#include "ECSInterfaces.h"
#include "RaceManager.h"
#include <algorithm>
#include <set>

class ScoreSystem : public ISystem
{
public:
	ScoreSystem()
	{
	}

	void process(float dt) override
	{
		std::vector<Player*> onScreen = RaceManager::getInstance()->getOnScreenPlayers();
		if (onScreen.size() == 1)
		{
			getComponentById<ScoreComponent>(RaceManager::getInstance()->getOnScreenPlayers().at(0)->ID)->rounds++;
			if (getComponentById<ScoreComponent>(RaceManager::getInstance()->getOnScreenPlayers().at(0)->ID)->rounds >= 3)
			{
				//DO WIN
				reset();
			}
		}
		else
		{
			if (AutoList::get<Player>().size() > 0 && onScreen.size() > 0)
			{
				std::vector<Player*> losers = difference(AutoList::get<Player>(), onScreen);
				for (std::vector<Player*>::iterator it = losers.begin(); it != losers.end(); ++it)
				{
					if ((*it)->getComponent<ScoreComponent>()->alive)
					{
						(*it)->getComponent<ScoreComponent>()->alive = false;
					}
				}
			}
		}
	}

	void reset()
	{
		for (auto& component : AutoList::get<ScoreComponent>())
		{
			component->rounds = 0;
			component->alive = true;
		}
	}

	std::vector<Player*> difference(std::vector<Player*> v1, std::vector<Player*> v2)
	{
		std::set<Player*> s1(v1.begin(), v1.end());
		std::set<Player*> s2(v2.begin(), v2.end());

		std::vector<Player*> result;

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());

		return result;
	}

private:

};
