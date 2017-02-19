#pragma once
#include "Entities.h"

class EntityFactory
{
public:
	static void SpawnPlayer(float x, float y, float w, float h);
	static void SpawnStaticBox(float x, float y, float w, float h);
	static void SpawnSoftBox(float x, float y, float w, float h);
	static void SpawnSlowShot(float x, float y, float w, float h, int targetID, int shooterID);
private:

};
