#pragma once
#include "Player.h"
#include "camera\Camera2D.h"
#include <numeric>

class RaceSystem : public ISystem
{
public:
	RaceSystem() {};

	void init()
	{
		for (auto& player : AutoList::get<Player>())
		{
			m_players.push_back(player);
		}
	}

	void process(float dt) override
	{
		std::vector<Player*> start;
		std::vector<Player*> end;

		end = m_players;

		if (m_players.front()->getComponent<RacePositionComponent>()->m_volumeID != 0)
		{
			while (start != end)
			{
				start = end; //If end is equal to start, no changes took place during sort
				for (std::vector<Player*>::iterator it = m_players.begin(); it != m_players.end() - 1; ++it)
				{
					if (Sort(**it, **(it + 1)))
					{
						std::swap(it, it + 1);
					}
				}
				end = m_players;
			}
		}

	}

	bool Sort(Player p1, Player p2)
	{
		if (p1.getComponent<RacePositionComponent>()->m_priority == 0 && p2.getComponent<RacePositionComponent>()->m_priority > 1)
		{
			return true;
		}
		else if (p2.getComponent<RacePositionComponent>()->m_priority == 0 && p1.getComponent<RacePositionComponent>()->m_priority > 1)
		{
			return false;
		}
		else if (p1.getComponent<RacePositionComponent>()->m_priority == p2.getComponent<RacePositionComponent>()->m_priority)
		{
			Vector2D direction = getComponentById<DirectionComponent>(p1.getComponent<RacePositionComponent>()->m_volumeID)->m_direction;

			std::vector<float> dir = { direction.x, direction.y };

			std::vector<float> p1Pos = { p1.getComponent<CollisionBoxComponent>()->body->GetPosition().x, p1.getComponent<CollisionBoxComponent>()->body->GetPosition().y };
			std::vector<float> p2Pos = { p2.getComponent<CollisionBoxComponent>()->body->GetPosition().x, p2.getComponent<CollisionBoxComponent>()->body->GetPosition().y };

			auto p1Product = std::inner_product(dir.begin(), dir.end(), p1Pos.begin(), p1Pos.end());
			auto p2Product = std::inner_product(dir.begin(), dir.end(), p2Pos.begin(), p2Pos.end());

			if (direction.x + direction.y > 0)
			{
				//Might not be orrect
				return p1Product > p2Product;
			}
			else
			{
				return p2Product > p1Product;
			}
		}
		else
		{
			return p1.getComponent<RacePositionComponent>()->m_priority > p2.getComponent<RacePositionComponent>()->m_priority;
		}
	}

	std::vector<Player*> getPositions()
	{
		return m_players;
	}

	Player* getLeader()
	{
		return m_players.front();
	}

private:
	std::vector<Player*> m_players;
};

