#pragma once
#include "Player.h"
#include "camera\Camera2D.h"
#include <numeric>

class RaceManager
{
public:
	static RaceManager *m_instance;

	std::vector<Player*> Sort();
	std::vector<Player*> getPlayers();
	Player* getLeader();

	static RaceManager *getInstance()
	{
		if (!m_instance)
		{
			m_instance = new RaceManager();
		}
		return m_instance;
	}

private:
	std::vector<Player*> m_players;
};

