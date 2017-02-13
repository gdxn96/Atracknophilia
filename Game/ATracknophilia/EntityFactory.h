#pragma once
#include "Entities.h"

class EntityFactory
{
public:
	static Player* SpawnPlayer(float x, float y, float w, float h);
	static StaticBox* SpawnStaticBox(float x, float y, float w, float h);
private:

};
