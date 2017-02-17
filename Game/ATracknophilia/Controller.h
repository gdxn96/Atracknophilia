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
		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new PressCommand([&]() {
			auto c = getComponent<CollisionBoxComponent>();
			if (c) 
			{
				c->body->SetGravityScale( -1);
			}
		}));

		InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new ReleaseCommand([&]() {
			isHoldingA = false;
			auto c = getComponent<CollisionBoxComponent>();
			if (c) {
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
				
				c->body->ApplyForceToCenter((dir * 10000).toBox2DVector(), true);
			}
			else
			{
				c->body->ApplyForceToCenter(b2Vec2(vec.x * 10000, 0), true);
			}
			
		}

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