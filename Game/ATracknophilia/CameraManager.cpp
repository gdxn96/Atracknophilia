#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager() : m_levelSize(0,0)
{
}

void CameraManager::update(float dt)
{
	std::vector<Camera2D::Point> points;
	auto players = AutoList::get<Player>();
	for (auto& player : players)
	{
		auto b = player->getComponent<Box2DComponent>();
		points.push_back(Camera2D::Point(b->body->GetPosition().x, b->body->GetPosition().y));
	}

	m_camera->zoomToFit(points, true);
	m_camera->update(dt * 1000);
	
}

void CameraManager::init(Camera2D::Camera * cam)
{
	m_camera = cam;
	float zoomSpeed = 0.01f; //speed the camera zooms in or out (smaller due to no deltaTime)
	float zoomToSpeed = 1000.f; //when using zoom to (no deltaTime)
	float minZoom = 2.f; //minimum level of zoom
	float maxZoom = 0.001f; //maximum threshold you can zoom in until;
	m_camera->setZoomProps(zoomSpeed, zoomToSpeed, minZoom, maxZoom);
}

void CameraManager::moveTo(Vector2D destination, float dt)
{
	Vector2D position = Vector2D(m_camera->getCentre().x, m_camera->getCentre().y);
	Vector2D difference = destination - position;
	Vector2D directionToPan = difference.Normalize();
	float distance = difference.Distance(position, difference);

	if (difference.Magnitude() > 1)
	{
		Vector2D result = position + (directionToPan * distance * dt / 2.f);

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