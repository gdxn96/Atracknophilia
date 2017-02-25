#include "stdafx.h"
#include "Controller.h"
#include "EntityFactory.h"

	
PlayerControllerComponent::PlayerControllerComponent(int id, int controllerId) : IControllerComponent(id, controllerId)
{
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		auto hook = getComponent<HookComponent>();
		if (c) {
			if (hook)
			{
				isHoldingA = true;
			}
			else
			{
				float xVelocity = InputManager::GetInstance()->GetLeftStickVectorNormal(m_controllerId).x;
				float xRay = 0;
				if (xVelocity > 0) { xRay = 1000; }
				else if (xVelocity < 0) { xRay = -1000; }
				auto intersection = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
				Vector2D intersectionPt = intersection.second;
				auto isStatic = intersection.first->getComponent<StaticBodyComponent>();
				float distance = Vector2D::Distance(Vector2D(c->body->GetPosition()), intersectionPt);
				if (distance > 10 && isStatic)
					getParent()->AddComponent(new HookComponent(ID, c->body->GetPosition(), intersectionPt, c->body));
			}
		}

	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new ReleaseCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			EntityFactory::SpawnSlowShot(c->body->GetPosition().x, c->body->GetPosition().y - 1, 1, 1, ID);
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_Y, new ReleaseCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			EntityFactory::SpawnWebDrop(c->body->GetPosition().x, c->body->GetPosition().y, 1, 1);
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c)
		{
			c->body->SetGravityScale(1);
			c->body->ApplyLinearImpulseToCenter(b2Vec2(0, -10), true);
		}

		auto l = getComponent<HookComponent>();
		if (l)
		{
			getParent()->deleteComponent<HookComponent>();
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new ReleaseCommand([&]() {
		isHoldingA = false;
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->SetGravityScale(1);
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_X, new HoldCommand([&]() {
		auto stamComp = getComponent<StaminaComponent>();
		if (stamComp && stamComp->stamina > 0)
		{
			getComponent<VelocityComponent>()->velocity = getComponent<ConstBoostedVelocityComponent>()->BOOSTED_VELOCITY;
			getComponent<AccelerationComponent>()->acceleration = getComponent<ConstBoostedAccelerationComponent>()->BOOSTED_ACCELERATION;
			stamComp->boostActive = true;
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_X, new ReleaseCommand([&]() {
		auto stamComp = getComponent<StaminaComponent>();
		if (stamComp)
		{
			stamComp->boostActive = false;
		}
	}), this, m_controllerId);
}

void PlayerControllerComponent::process(float dt)
{
	auto vec = InputManager::GetInstance()->GetLeftStickVectorNormal(m_controllerId);
	auto c = getComponent<Box2DComponent>();
	if (c)
	{
		auto h = getComponent<HookComponent>();
		auto a = getComponent<AccelerationComponent>();
		if (h && vec.x != 0 && a)
		{
			auto dir = Vector2D::Perpendicular((h->line->end - h->line->start).Normalize()) * vec.x / std::fabs(vec.x);
			c->body->ApplyForceToCenter((dir * a->acceleration).toBox2DVector(), true);
		}
		else
		{
			c->body->ApplyForceToCenter(b2Vec2(vec.x * a->acceleration, 0), true);
		}
		std::cout << "Acceleration: " << a->acceleration << std::endl;
	}

	auto hook = getComponent<HookComponent>();
	if (hook)
	{
		if (!hook->alive)
		{
			getParent()->deleteComponent<HookComponent>();
			return;
		}
		if (isHoldingA)
		{
			hook->decreaseTetherLength(dt);
		}
		else
		{
			hook->increaseTetherLength(dt);
		}
	}

}