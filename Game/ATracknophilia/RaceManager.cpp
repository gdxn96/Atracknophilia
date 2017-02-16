#include "stdafx.h"
#include "RaceManager.h"
#include <set>

RaceManager *RaceManager::m_instance = 0;

std::vector<Player*> RaceManager::Sort()
{
	auto players = AutoList::get<Player>();
	std::set<int> volumeIDs;
	std::vector<Player*> sortedList;
	std::unordered_map<int, std::unordered_map < int, std::pair<int, std::vector<Player* >>> > playerLapsMap;
	std::set<int> playerLaps;

	for (auto player : players)
	{
		auto dirVolume = getComponentById<DirectionVolume>(player->getComponent<RacePositionComponent>()->volumeID);
		if (dirVolume)
		{
			int volume = dirVolume->getComponent<PriorityComponent>()->m_priority;
			int volumeId = dirVolume->ID;
			int lap = player->getComponent<RacePositionComponent>()->lap;
			playerLapsMap[lap][volume].first = volumeId;
			playerLapsMap[lap][volume].second.push_back(player);
			volumeIDs.insert(volume);
			playerLaps.insert(lap);
		}
	}

	/*
		playerLapsMap 
		{
			lapNum : {
					volumeId : [
							Player,
							Player
						],
					volumeId : [
						Player,
						Player
					]
				}
		}
	
	
	*/

	for (auto lapVolumes : playerLapsMap)
	{
		for (auto volumePlayers : lapVolumes.second)
		{
			int volumeId = volumePlayers.second.first;
			auto& players = volumePlayers.second.second;
			Vector2D volumeDirection = getComponentById<DirectionVolume>(volumeId)->getComponent<DirectionComponent>()->m_direction;
			std::sort(players.begin(), players.end(), [&](Player* p1, Player* p2) {
				return	Vector2D::DotProduct(volumeDirection, p1->getComponent<Box2DComponent>()->body->GetPosition()) >
					Vector2D::DotProduct(volumeDirection, p2->getComponent<Box2DComponent>()->body->GetPosition());
			});
		}
	}

	for (int lap : playerLaps)
	{
		for (int volume : volumeIDs)
		{
			for (auto player : playerLapsMap[lap][volume].second)
			{
				sortedList.push_back(player);
			}
		}
	}

	return sortedList;
}

std::vector<Player*> RaceManager::getPlayers()
{
	return Sort();
}

Player* RaceManager::getLeader()
{
	 auto x = Sort().back();
	 return x;
}