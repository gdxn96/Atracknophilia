#pragma once
#include "ECSInterfaces.h"
#include "Priority.h"

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
			int priority = getComponentById<PriorityComponent>(volumeID)->priority;
			int newPriority = getComponentById<PriorityComponent>(id)->priority;
			if (newPriority == 0 && priority > 1)
			{
				lap++;
			}
			if (priority == 0 && newPriority > 1)
			{
				lap--;
			}

			std::cout << "Player " << ID << " Position: " << newPriority << " Lap: " << lap << std::endl;
		}

		volumeID = id;
	}

	int lap;
	int volumeID;
};
