#pragma once
#include "Components.h"

class WebDrop : public IEntity, public AutoLister<WebDrop>
{
public:
	WebDrop(int id, int x, int y, int w, int h, AudioManager* audioMgr) : IEntity(id,
	{
		new WebDropComponent(id, x, y, w, h),
		new WebDropResponseComponent(id, audioMgr),
	})
	{};


private:

};