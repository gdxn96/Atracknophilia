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

SoftBox* EntityFactory::SpawnSoftBox(float x, float y, float w, float h)
{
	return new SoftBox(id(), x, y, w, h);
}

DirectionVolume * EntityFactory::SpawnDirectionVolume(float x, float y, float w, float h, int priority, Vector2D direction)
{
	return new DirectionVolume(id(), x, y, w, h, priority, direction);
}
