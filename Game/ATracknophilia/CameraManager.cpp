#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager() : m_levelSize(0,0)
{
}

void CameraManager::update(float dt)
{
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
		m_camera->zoom(0);
	}
	
	auto players = RaceManager::getInstance()->getPlayers();
	/*if (players.size() > 1)
	{
		Vector2D dist = players[0]->getComponent<Box2DComponent>()->body->GetPosition() - players.back()->getComponent<Box2DComponent>()->body->GetPosition();
		Vector2D centre = Vector2D(players[0]->getComponent<Box2DComponent>()->body->GetPosition()) - dist / 2;
		m_camera->setCentre(Camera2D::Point(centre.x, centre.y));
	}*/

	float highx = -1, lowx = std::numeric_limits<float>::max(), lowy = std::numeric_limits<float>::max(), highy = -1;
	for (auto& player : players)
	{
		Vector2D pos = player->getComponent<Box2DComponent>()->body->GetPosition();
		if (pos.x > highx)
		{
			highx = pos.x;
		}
		if (pos.x < lowx)
		{
			lowx = pos.x;
		}
		if (pos.y > highy)
		{
			highy = pos.y;
		}
		if (pos.y < lowy)
		{
			lowy = pos.y;
		}
	}

	if (highx > -1)
		moveTo(Vector2D(highx - ((highx - lowx) * 0.5), highy - ((highy - lowy) * 0.5)), dt);


	
}

void CameraManager::init(Camera2D::Camera * cam)
{
	m_camera = cam;
}

void CameraManager::moveTo(Vector2D destination, float dt)
{

		m_camera->setCentre(destination.x, destination.y);		

	
}

Camera2D::Camera * CameraManager::getCamera()
{
	return m_camera;
}

void CameraManager::SetLevelSize(Vector2D size)
{
	m_levelSize = size;
}