#pragma once
#include "Player.h"
#include "StaticPolygon.h"


static int id()
{
	static int x = 0;
	x++;
	return x;
}