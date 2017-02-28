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
			Player* winner = onScreen.at(0);
			getComponentById<ScoreComponent>(winner->ID)->rounds++;
			//new round
			for (auto& player : AutoList::get<Player>())
			{
				player->getComponent<DynamicBodyComponent>()->body->SetTransform(winner->getComponent<DynamicBodyComponent>()->body->GetPosition(), 0);
			}
			if (getComponentById<ScoreComponent>(winner->ID)->rounds >= 3)
			{
				//DO WIN & New game
				cout << "winner: " << winner->ID << endl;
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
		std::vector<Player*>::iterator it;

		std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(result));

		if (result.size() > 0)
		{
			int i = 0;
		}

		return result;
	}

private:

};
