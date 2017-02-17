#pragma once
#include "Logic.h"
#include "Dimensional.h"

class DirectionVolumeCollisionResponseComponent;

class DirectionVolume : public IEntity, public AutoLister<DirectionVolume>
{
public:
	DirectionVolume(int id, float x, float y, float w, float h, int priority, Vector2D direction);
private:

};
