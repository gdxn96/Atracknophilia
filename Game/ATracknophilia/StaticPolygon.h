#pragma once
#include "Components.h"

class StaticBox : public IEntity
{
public:
	StaticBox(int id, float x, float y, float w, float h) : IEntity(id,
	{
		new StaticBodyComponent(id, x, y, w, h, true)
	})
	{

	}

private:

};
