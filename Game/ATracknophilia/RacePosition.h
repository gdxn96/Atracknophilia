#pragma once
#include "ECSInterfaces.h"

struct RacePositionComponent : public IComponent, public AutoLister<RacePositionComponent>
{
	RacePositionComponent(int id)
		:	IComponent(id)
		,	volumeID(-1)
		,	lap(0)
	{
	}

	void SetVolumeId(int id)
	{
		if (volumeID != -1)
		{
			int priority = getComponentById<PriorityComponent>(volumeID)->m_priority;
			if (id == 0 && priority != 1)
			{
				lap++;
			}
			if (priority == 0 && id > 1)
			{
				lap--;
			}
		}

		volumeID = id;
	}

	int lap;
	int volumeID;
};
