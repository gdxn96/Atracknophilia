#pragma once
#include "Components.h"

class WebDrop : public IEntity
{
public:
	WebDrop(int id, int x, int y, int w, int h, int shooterID) : IEntity(id,
	{
		new WebDropComponent(id, x, y, w, h),
		new WebDropResponseComponent(id, shooterID),
	})
	{};


private:

};