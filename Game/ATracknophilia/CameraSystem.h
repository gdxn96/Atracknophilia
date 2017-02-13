#pragma once
#include "Player.h"
#include "camera\Camera2D.h"

class CameraSystem : public ISystem
{
public:
	CameraSystem()
	{

	}
	void process(float dt) override
	{
		auto ents = AutoList::get<Player>();

	}

private:

};

