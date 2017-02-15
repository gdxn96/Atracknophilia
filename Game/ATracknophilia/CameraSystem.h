#pragma once
#include "Player.h"
#include "camera\Camera2D.h"

class CameraSystem : public ISystem
{
public:
	CameraSystem(){}

	void process(float dt) override
	{
		//m_camera->setCentre(m_players.front()->getComponent<CollisionBoxComponent>()->body->GetPosition().x, m_players.front()->getComponent<CollisionBoxComponent>()->body->GetPosition().y);
	}

	void init(Camera2D::Camera * cam)
	{
		m_camera = cam;
	}

private:
	Camera2D::Camera * m_camera;
};

