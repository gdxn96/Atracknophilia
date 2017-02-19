#pragma once
#include "Entities.h"

class EntityFactory
{
public:
	static Player* SpawnPlayer(float x, float y, float w, float h, int controllerIds);
	static StaticBox* SpawnStaticBox(float x, float y, float w, float h);
	static SoftBox* SpawnSoftBox(float x, float y, float w, float h);
	static DirectionVolume* SpawnDirectionVolume(float x, float y, float w, float h, int priority, Vector2D direction);
private:

};
