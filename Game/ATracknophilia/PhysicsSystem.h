#pragma once
#include "ECSInterfaces.h"
#include "box2d\Box2D.h"

class PhysicsSystem : public ISystem
{
public:
	void process(float dt) override;

	static b2Vec2& Gravity();

	static b2World& World();
private:

};
