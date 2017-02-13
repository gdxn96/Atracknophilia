#include "stdafx.h"
#include "EntityFactory.h"

Player* EntityFactory::SpawnPlayer(float x, float y, float w, float h)
{
	return new Player(id(), x, y, w, h);
}

StaticBox* EntityFactory::SpawnStaticBox(float x, float y, float w, float h)
{
	return new StaticBox(id(), x, y, w, h);
}
