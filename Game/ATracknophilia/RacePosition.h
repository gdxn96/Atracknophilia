#pragma once
#include "ECSInterfaces.h"

struct RacePositionComponent : public IComponent, public AutoLister<RacePositionComponent>
{
	RacePositionComponent(int id)
		:	IComponent(id)
		,	volumeID(88)
		,	lap(0)
	{
	}

	void SetVolumeId(int id)
	{
		if (id == 0 && volumeID != 1)
		{
			lap++;
		}
		if (volumeID == 0 && id > 1)
		{
			lap--;
		}
	}

	int lap;
	int volumeID;
};
