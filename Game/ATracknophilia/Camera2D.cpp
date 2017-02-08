#include "stdafx.h"
#include "Camera2D.h"

Camera2D::Camera2D(Rect viewPort, float initScale) : m_viewPort(viewPort), m_scale(initScale), m_scaleUnit(1.1f), m_levelSize(Vector2D(1, 1))
{
}

Rect Camera2D::getViewport()
{
	return m_viewPort;
}

float Camera2D::getScale()
{
	return m_scale;
}

void Camera2D::setCenter(Vector2D centre)
{
	centre = centre * m_scale;
	m_viewPort.pos.x = centre.x - (m_viewPort.size.w / 2);
	m_viewPort.pos.y = centre.y - (m_viewPort.size.h / 2);
	limitValues();
}

void Camera2D::increaseScale()
{
	Vector2D centre(m_viewPort.getCentreCopy());
	centre = centre / m_scale;

	m_scale *= m_scaleUnit;

	centre = centre * m_scale;
	m_viewPort.pos.x = centre.x - (m_viewPort.size.w / 2);
	m_viewPort.pos.y = centre.y - (m_viewPort.size.h / 2);
	limitValues();
}

void Camera2D::decreaseScale()
{
	Vector2D centre(m_viewPort.getCentreCopy());
	centre = centre / m_scale;

	m_scale /= m_scaleUnit;
	if (m_scale < 1)
	{
		m_scale = 1;
	}

	centre = centre * m_scale;
	m_viewPort.pos.x = centre.x - (m_viewPort.size.w / 2);
	m_viewPort.pos.y = centre.y - (m_viewPort.size.h / 2);
	limitValues();
}

void Camera2D::setLevelSize(Vector2D size)
{
	m_levelSize = size;
}

void Camera2D::limitValues()
{
	if (m_viewPort.pos.x > m_levelSize.w * m_scale - m_viewPort.size.w)
	{
		m_viewPort.pos.x = m_levelSize.w * m_scale - m_viewPort.size.w;
	}
	if (m_viewPort.pos.x < 0)
	{
		m_viewPort.pos.x = 0;
	}
	if (m_viewPort.pos.y > m_levelSize.h * m_scale - m_viewPort.size.h)
	{
		m_viewPort.pos.y = m_levelSize.h * m_scale - m_viewPort.size.h;
	}
	if (m_viewPort.pos.y < 0)
	{
		m_viewPort.pos.y = 0;
	}
}
