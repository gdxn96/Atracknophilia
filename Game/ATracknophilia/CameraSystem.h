#pragma once
#include "Player.h"
#include "camera\Camera2D.h"
#include "RaceManager.h"

class CameraSystem : public ISystem
{
public:
	CameraSystem(){}

	void process(float dt) override
	{
		Vector2D leaderPos = RaceManager::getInstance()->getLeader()->getComponent<CollisionBoxComponent>()->body->GetPosition();
		m_camera->setCentre(leaderPos.x, leaderPos.y);
	}

	void init(Camera2D::Camera * cam)
	{
		m_camera = cam;
	}

private:
	Camera2D::Camera * m_camera;
};

