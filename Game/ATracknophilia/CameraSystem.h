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
		for (auto& component : AutoList::get<Player>())
		{
			m_cam->setCentre(component->)
		}
	}

private:
	Camera2D::Camera * m_cam;
};

