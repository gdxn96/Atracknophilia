#include "stdafx.h"
#include "EntityFactory.h"
#include "LevelLoader.h"

void EntityFactory::SpawnPlayer(float x, float y, float w, float h)
{
	LevelLoader::appendToEntities(new Player(id(), x, y, w, h));
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