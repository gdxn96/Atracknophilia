#pragma once
#include "ECSInterfaces.h"

struct RacePositionComponent : public IComponent, public AutoLister<RacePositionComponent>
{
	RacePositionComponent(int id, int priority, int volumeID)
		: IComponent(id)
		, m_priority(priority)
		, m_volumeID(volumeID)
	{
	}

	void update(int priority, int id)
	{
		m_priority = priority;
		m_volumeID = id;
	}

	int m_priority;
	int m_volumeID;
};
