#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"
#include "FLInput\FLInputManager.h"

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

	virtual void process() = 0;
};

struct PlayerControllerComponent : public IControllerComponent
{
	PlayerControllerComponent(int id) : IControllerComponent(id)
	{
		InputManager::GetInstance()->AddKey(EventListener::ARROW_LEFT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {  
				c->body->ApplyForceToCenter(b2Vec2(-10000, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::ARROW_RIGHT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(10000, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_LEFT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(-10000, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_RIGHT, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->ApplyForceToCenter(b2Vec2(10000, 0), true);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new HoldCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
				c->body->SetGravityScale(-1);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new PressCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c && c->body->GetContactList() && c->body->GetGravityScale() < 0) {
				c->body->SetGravityScale(1);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new ReleaseCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c && !c->body->GetContactList()) {
				c->body->SetGravityScale(1);
			}
		}));
	}

	void process() override
	{
		auto vec = InputManager::GetInstance()->GetLeftStickVectorNormal();
		auto c = getComponent<CollisionBoxComponent>();
		c->body->ApplyForceToCenter(b2Vec2(vec.x * 10000, 0), true);
	}
};