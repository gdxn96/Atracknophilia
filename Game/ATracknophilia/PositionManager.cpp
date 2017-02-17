#include "stdafx.h"
#include "PositionManager.h"

PositionManager::PositionManager()
{
	m_first = AutoList::get<Player>().at(0)->ID;
	if (AutoList::get<Player>().at(1)){
		m_second = AutoList::get<Player>().at(1)->ID;
	}
	if (AutoList::get<Player>().at(2)) {
		m_second = AutoList::get<Player>().at(2)->ID;
	}
	if (AutoList::get<Player>().at(3)) {
		m_second = AutoList::get<Player>().at(3)->ID;
	}
}

void PositionManager::BeginContact(b2Contact * contact)
{
	//if (contact->GetFixtureA()->GetUserData == "Player" && contact->GetFixtureB()->GetUserData == "Sensor")
	//{
	//	for (auto& volume : AutoList::get<DirectionVolume>())
	//	{
	//		if (volume->getComponent<CollisionBoxComponent>()->body == contact->GetFixtureB()->GetBody())
	//		{
	//			if (volume->getComponent<PriorityComponent>()->m_priority > m_priority)
	//			{
	//				m_priority = volume->getComponent<PriorityComponent>()->m_priority;

	//				for (auto& player : AutoList::get<Player>())
	//				{
	//					if (player->getComponent<CollisionBoxComponent>()->body == contact->GetFixtureA()->GetBody())
	//					{
	//						m_first = player->ID;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//else if (contact->GetFixtureB()->GetUserData == "Player" && contact->GetFixtureA()->GetUserData == "Sensor")
	//{

	//}
}

int PositionManager::getFirst()
{
	return m_first;
}

Vector2D PositionManager::getDiretion()
{
	return m_direction;
}

std::vector<int> PositionManager::getPositions()
{
	return std::vector<int>() = { m_first,m_second,m_third,m_fourth };
}


