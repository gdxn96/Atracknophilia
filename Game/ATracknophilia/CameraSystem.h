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
		Player *leader = RaceManager::getInstance()->getLeader();

		int volumeID;

		auto raceComponent = leader->getComponent<RacePositionComponent>();
		
		if (raceComponent)
		{
			volumeID = raceComponent->volumeID;
		}


		Vector2D direction = getComponentById<DirectionComponent>(volumeID)->m_direction;

		if (direction.x == 0)
		{
			m_camera->setAllowedHorizontal(true);
		}
		else
		{
			m_camera->setAllowedHorizontal(false);
		}
		if (direction.y == 0)
		{
			m_camera->setAllowedVertical(true);
		}
		else
		{
			m_camera->setAllowedVertical(false);
		}

		if (RaceManager::getInstance()->getLeader()->getComponent<CollisionBoxComponent>())
		{
			moveTo(RaceManager::getInstance()->getLeader()->getComponent<CollisionBoxComponent>()->body->GetPosition());
		}
	}

	void init(Camera2D::Camera * cam)
	{
		m_camera = cam;
	}

	void moveTo(Vector2D destination)
	{
		Vector2D position = Vector2D(m_camera->getCentre().x, m_camera->getCentre().y);
		Vector2D difference = destination - position;

		if (difference.Magnitude() > 1)
		{
			Vector2D result = position + (difference * 0.005f);
			m_camera->setCentre( result.x, result.y);
		}
		else
		{
			m_camera->setCentre(destination.x, destination.y);
		}		
	}

private:
	Camera2D::Camera * m_camera;
};

