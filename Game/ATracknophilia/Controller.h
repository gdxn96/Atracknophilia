#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"
#include "FLInput\FLInputManager.h"
#include "Drawables.h"
#include "Interactables.h"

class PressCommand : public Command
{
public:
	PressCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Press) {};
	void executePress() {
		m_function();
	};

private:

};
class HoldCommand : public Command
{
public:
	HoldCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Hold) {};
	void executeHold() {
		m_function();
	};
private:

};
class ReleaseCommand : public Command
{
public:
	ReleaseCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Release) {};
	void executeRelease() {
		m_function();
	};

private:

};


struct IControllerComponent : public IComponent, public AutoLister<IControllerComponent>
{
	IControllerComponent(int id) : IComponent(id)
	{

	}

	virtual void process(float dt) = 0;
};

struct PlayerControllerComponent : public IControllerComponent
{
	PlayerControllerComponent(int id) : IControllerComponent(id)
	{
		InputManager::GetInstance()->AddKey(EventListener::ARROW_LEFT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {  
				c->body->ApplyForceToCenter(b2Vec2(-100, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::ARROW_RIGHT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(100, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_LEFT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(-100, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_RIGHT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(100, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			auto hook = getComponent<HookComponent>();
			if (c) {
				if (hook)
				{
					isHoldingA = true;
				}
				else
				{
					float xVelocity = InputManager::GetInstance()->GetLeftStickVectorNormal().x;
					float xRay = 0;
					if (xVelocity > 0) { xRay = 1000; }
					else if (xVelocity < 0) { xRay = -1000; }
					Vector2D intersectionPt = PhysicsSystem::RayCast(c->body->GetPosition(), Vector2D(c->body->GetPosition()) + Vector2D(xRay, -1000));
					getParent()->AddComponent(new HookComponent(ID, c->body->GetPosition(), intersectionPt, c->body));
				}
			}
			
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new PressCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c && c->body->GetContactList()) 
			{
				c->body->SetGravityScale(1);
				c->body->ApplyLinearImpulseToCenter(b2Vec2(0, -100), true);
			}

			auto l = getComponent<HookComponent>();
			if (l)
			{
				getParent()->deleteComponent<HookComponent>();
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new ReleaseCommand([&]() {
			isHoldingA = false;
			auto c = getComponent<CollisionBoxComponent>();
			if (c && !c->body->GetContactList()) {
				c->body->SetGravityScale(1);
			}
		}));

		
	}

	void process(float dt) override
	{
		auto vec = InputManager::GetInstance()->GetLeftStickVectorNormal();
		auto c = getComponent<CollisionBoxComponent>();
		if (c)
		{
			auto h = getComponent<HookComponent>();
			if (h && vec.x != 0)
			{
				auto dir = Vector2D::Perpendicular((h->line->end - h->line->start).Normalize()) * vec.x / std::fabs(vec.x);
				
				c->body->ApplyForceToCenter((dir * 100).toBox2DVector(), true);
			}
			else
			{
				c->body->ApplyForceToCenter(b2Vec2(vec.x * 100, 0), true);

			}
			
		}

		std::cout << Vector2D(c->body->GetLinearVelocity()).Magnitude() << std::endl;

		auto hook = getComponent<HookComponent>();
		if (hook)
		{
			auto c = getComponent<CollisionBoxComponent>();
			if (c && c->body->GetContactList())
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

	bool isHoldingA = false;
};