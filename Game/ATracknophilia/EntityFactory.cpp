#include "stdafx.h"
#include "EntityFactory.h"
#include "LevelLoader.h"


void EntityFactory::SpawnPlayer(float x, float y, float w, float h, int controllerId)
{
	LevelLoader::appendToEntities(new Player(id(), x, y, w, h, controllerId));
}

void EntityFactory::SpawnStaticBox(float x, float y, float w, float h)
{
	LevelLoader::appendToEntities(new StaticBox(id(), x, y, w, h));
}

void EntityFactory::SpawnSoftBox(float x, float y, float w, float h)
{
	LevelLoader::appendToEntities(new SoftBox(id(), x, y, w, h));
}

void EntityFactory::SpawnSlowShot(float x, float y, float w, float h, int targetID, int shooterID)
{
	// get target id
	LevelLoader::appendToEntities(new SlowShot(id(), x, y, w, h, targetID, shooterID));
}

void EntityFactory::SpawnDirectionVolume(float x, float y, float w, float h, int priority, Vector2D direction)
{
	LevelLoader::appendToEntities(new DirectionVolume(id(), x, y, w, h, priority, direction));
}

void EntityFactory::SpawnStaticPoly(const b2Vec2 * vec)
{
	LevelLoader::appendToEntities(new StaticPoly(id(), vec));
}