#pragma once
#include "stdafx.h"
#include <vector>
#include "Player.h"
#include "box2d\Box2D.h"
#include "DirectionVolume.h"

class PositionManager : public b2ContactListener
{
private:
	int m_first, m_second, m_third, m_fourth;
	int m_priority = 0;
	Vector2D m_direction = Vector2D(0,0);
public:
	PositionManager();

	virtual void BeginContact(b2Contact* contact);

	int getFirst();
	Vector2D getDiretion();
	std::vector<int> getPositions();
};

