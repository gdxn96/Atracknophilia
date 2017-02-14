#pragma once
#include "Player.h"
#include "camera\Camera2D.h"

class CameraSystem : public ISystem
{
public:
	CameraSystem(){}

	void process(float dt) override
	{
		Player* leader = AutoList::get<Player>().at(0);
		bool first = true;

		for (auto& player : AutoList::get<Player>())
		{
			if (first)
			{
				first = false;
			}
			else
			{
				if (m_direction == Direction::NORTH && player->getComponent<CollisionBoxComponent>()->body->GetPosition().y < leader->getComponent<CollisionBoxComponent>()->body->GetPosition().y) {
					leader = player;
				}
				else if (m_direction == Direction::EAST && player->getComponent<CollisionBoxComponent>()->body->GetPosition().x > leader->getComponent<CollisionBoxComponent>()->body->GetPosition().x) {
					leader = player;
				}
				else if (m_direction == Direction::SOUTH && player->getComponent<CollisionBoxComponent>()->body->GetPosition().y > leader->getComponent<CollisionBoxComponent>()->body->GetPosition().y) {
					leader = player;
				}
				else if (m_direction == Direction::WEST && player->getComponent<CollisionBoxComponent>()->body->GetPosition().x < leader->getComponent<CollisionBoxComponent>()->body->GetPosition().x) {
					leader = player;
				}
			}
		}

		m_camera->setCentre(leader->getComponent<CollisionBoxComponent>()->body->GetPosition().x, leader->getComponent<CollisionBoxComponent>()->body->GetPosition().y);
	}

	void init(Camera2D::Camera * cam)
	{
		m_camera = cam;
	}

	void dir(int d)
	{
		m_direction = d;
	}

private:
	Camera2D::Camera * m_camera;
	int m_direction = -1;
};

