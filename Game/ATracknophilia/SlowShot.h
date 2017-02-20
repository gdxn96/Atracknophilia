#pragma once
#include "Components.h"

class SlowShot : public IEntity
{
public:
	SlowShot(int id, float x, float y, float w, float h, int targetID, int shooterID)
		: IEntity(id,
		{
			new SlowShotComponent(id, x, y, w, h, false, false),
			new SeekAIComponent(id, targetID, shooterID),
			new SlowShotResponseComponent(id)
		})
	{}

};
