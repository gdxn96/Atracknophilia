#pragma once
#include "Components.h"

class InvertGravityOnEdgeComponent;

class Player : public IEntity, public AutoLister<Player>
{
public:
	Player(int id, float x, float y, float w, float h);
private:

};

