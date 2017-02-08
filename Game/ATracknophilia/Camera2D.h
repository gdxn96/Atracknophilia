#pragma once
#include "BasicTypes.h"

class Camera2D
{
public:
	Camera2D(Rect viewPort, float initScale);
	Rect getViewport();
	float getScale();

	void setCenter(Vector2D v);

	void increaseScale();
	void decreaseScale();

	void setLevelSize(Vector2D size);

private:
	Rect m_viewPort;
	Vector2D m_levelSize;
	float m_scale;
	float m_scaleUnit;

	void limitValues();
};