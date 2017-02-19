#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager() : m_levelSize(0,0)
{
}

void CameraManager::update(float dt)
{
	Player *leader = RaceManager::getInstance()->getLeader();

	int volumeID;

	if (leader)
	{
		auto raceComponent = leader->getComponent<RacePositionComponent>();

		if (raceComponent)
		{
			volumeID = raceComponent->volumeID;
		}

		if (RaceManager::getInstance()->getLeader()->getComponent<CollisionBoxComponent>())
		{
			moveTo(RaceManager::getInstance()->getLeader()->getComponent<CollisionBoxComponent>()->body->GetPosition(), dt);
		}
	}
}

void CameraManager::init(Camera2D::Camera * cam)
{
	m_camera = cam;
}

void CameraManager::moveTo(Vector2D destination, float dt)
{
	Vector2D position = Vector2D(m_camera->getCentre().x, m_camera->getCentre().y);
	Vector2D difference = destination - position;
	Vector2D directionToPan = difference.Normalize();
	float distanceSq = difference.Distance(position, difference);

	if (difference.Magnitude() > 1)
	{
		Vector2D result = position + (directionToPan * distanceSq * dt);

		m_camera->setCentre(result.x, result.y);

		auto cameraBounds = m_camera->getBounds();

		int halfCameraWidth = cameraBounds.w / 2.0f;
		int halfCameraHeight = cameraBounds.h / 2.0f;

		auto centre = m_camera->getCentre();
		if (cameraBounds.x < 0)
		{
			m_camera->setCentre(halfCameraWidth, centre.y);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.y < 0)
		{
			m_camera->setCentre(centre.x, halfCameraHeight);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.x + cameraBounds.w > m_levelSize.w)
		{
			m_camera->setCentre(m_levelSize.w - halfCameraWidth, centre.y);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.y + cameraBounds.h >  m_levelSize.h)
		{
			m_camera->setCentre(centre.x, m_levelSize.h - halfCameraHeight);
			centre = m_camera->getCentre();
		}
	}
	else
	{
		m_camera->setCentre(destination.x, destination.y);

		auto cameraBounds = m_camera->getBounds();

		int halfCameraWidth = cameraBounds.w / 2.0f;
		int halfCameraHeight = cameraBounds.h / 2.0f;

		auto centre = m_camera->getCentre();
		if (cameraBounds.x < 0)
		{
			m_camera->setCentre(halfCameraWidth, centre.y);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.y < 0)
		{
			m_camera->setCentre(centre.x, halfCameraHeight);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.x + cameraBounds.w > m_levelSize.w)
		{
			m_camera->setCentre(m_levelSize.w - halfCameraWidth, centre.y);
			centre = m_camera->getCentre();
		}

		if (cameraBounds.y + cameraBounds.h >  m_levelSize.h)
		{
			m_camera->setCentre(centre.x, m_levelSize.h - halfCameraHeight);
			centre = m_camera->getCentre();
		}
	}
}

void CameraManager::SetLevelSize(Vector2D size)
{
	m_levelSize = size;
}