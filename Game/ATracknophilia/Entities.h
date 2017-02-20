#pragma once
#include "Player.h"
#include "StaticPolygon.h"
#include "DirectionVolume.h"
#include "SoftBox.h"
#include "SlowShot.h"


static int id()
{
	static int x = 0;
	x++;
	return x;
}