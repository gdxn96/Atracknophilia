#include "stdafx.h"
#include "Controller.h"
#include "EntityFactory.h"
#include "RaceManager.h"
#include "Drawables.h"
#include "Interactables.h"
#include "Property.h"
#include "Dimensional.h"
#include "AudioManager.h"
	
PlayerControllerComponent::PlayerControllerComponent(int id, int controllerId, AudioManager* audioMgr) 
	: IControllerComponent(id, controllerId)
	, m_audioMgr(audioMgr)
{
	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_B, new ReleaseCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		auto a = getComponent<AbilityComponent>();
		if (c && a) {
			const auto none = a->NONE;
			const auto webDrop = a->WEB_DROP;
			const auto slowShot = a->SLOW_SHOT;
			const auto swapShot = a->SWAP_SHOT;

			switch (a->ability)
			{
			case none:
				break;
			case webDrop:
				if (Vector2D(c->body->GetLinearVelocity()).Normalize().x > 0)
				{
					EntityFactory::SpawnWebDrop(c->body->GetPosition().x - 5, c->body->GetPosition().y, 4, 4, m_audioMgr);
				}
				else if (Vector2D(c->body->GetLinearVelocity()).Normalize().x < 0)
				{
					EntityFactory::SpawnWebDrop(c->body->GetPosition().x + 5, c->body->GetPosition().y, 4, 4, m_audioMgr);
				}
				else
				{
					EntityFactory::SpawnWebDrop(c->body->GetPosition().x, c->body->GetPosition().y - (5), 4, 4, m_audioMgr);
				}
				a->ability = a->NONE;
				notify(Observer::DROP);
				break;
			case slowShot:
				EntityFactory::SpawnSlowShot(c->body->GetPosition().x, c->body->GetPosition().y - 1, 1, 1, ID);
				a->ability = a->NONE;
				notify(Observer::SHOOT);
				break;
			case swapShot:
				auto h = getComponent<HookComponent>();
				if (h)
				{
					getParent()->deleteComponent<HookComponent>();
				}
				vector<Player*> players = RaceManager::getInstance()->getPlayers();
				int targetID = 1;
				for (int i = 0; i < players.size(); i++)
				{
					if (i + 1 == players.size())
					{}
					else if (players[i]->ID == ID)
					{
						auto targetBody = players[i + 1]->getComponent<Box2DComponent>()->body;
						auto obstacle = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), targetBody->GetPosition(), 50);
						if (!obstacle.first)
						{
							b2Vec2 dis = (c->body->GetPosition() - targetBody->GetPosition());
							getParent()->AddComponent(new SwapComponent(ID, c->body->GetPosition(), targetBody->GetPosition(), c->body, players[i + 1]));
							auto hook = players[i + 1]->getComponent<HookComponent>();
							if (hook)
							{
								players[i + 1]->deleteComponent<HookComponent>();
							}
							targetBody->SetLinearVelocity(b2Vec2(0, 0));
							targetBody->ApplyForceToCenter(b2Vec2(dis.x * 100000, dis.y * 100000), true);
							c->body->ApplyForceToCenter(b2Vec2(-dis.x * 100000, -dis.y * 100000), true);
							isHooked = true;
							if (players[i + 1]->getComponent<PlayerAIComponent>())
							{
								players[i + 1]->getComponent<PlayerAIComponent>()->isHooked = true;
							}
							else if(players[i + 1]->getComponent<PlayerControllerComponent>())
							{
								players[i + 1]->getComponent<PlayerControllerComponent>()->isHooked = true;
							}
							targetBody->SetGravityScale(0);
							c->body->SetGravityScale(0);
							notify(Observer::SWAP_SHOT);
						}
						i = players.size();
					}
				}
				a->ability = a->NONE;
				break;
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new HoldCommand([&]() {
		if (!isHooked)
		{
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
					if(intersection.first)
					{ 
						Vector2D intersectionPt = intersection.second;
						auto isDynamic = intersection.first->getComponent<StaticBodyComponent>();
						float distance = Vector2D::Distance(Vector2D(c->body->GetPosition()), intersectionPt);
						if (distance > 10 && isDynamic)
						{
							getParent()->AddComponent(new HookComponent(ID, c->body->GetPosition(), intersectionPt, c->body));
							notify(Observer::HOOK);
						}
					}
				}
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new PressCommand([&]() {
		if (!isHooked)
		{
			auto c = getComponent<Box2DComponent>();
			if (c)
			{
				c->body->SetGravityScale(1);
				c->body->ApplyLinearImpulseToCenter(b2Vec2(0, -10), true);
				//notify(Observer::JUMP);
			}

			auto l = getComponent<HookComponent>();
			if (l)
			{
				getParent()->deleteComponent<HookComponent>();
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_A, new ReleaseCommand([&]() {
		if (!isHooked)
		{
			isHoldingA = false;
			auto c = getComponent<Box2DComponent>();
			if (c) {
				c->body->SetGravityScale(1);
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_X, new HoldCommand([&]() {
		if (!isHooked)
		{
			auto stamComp = getComponent<StaminaComponent>();
			if (stamComp && stamComp->stamina > 0)
			{
				getComponent<VelocityComponent>()->velocity = getComponent<ConstBoostedVelocityComponent>()->BOOSTED_VELOCITY;
				getComponent<AccelerationComponent>()->acceleration = getComponent<ConstBoostedAccelerationComponent>()->BOOSTED_ACCELERATION;
				stamComp->boostActive = true;
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_X, new ReleaseCommand([&]() {
		if (!isHooked)
		{
			auto stamComp = getComponent<StaminaComponent>();
			if (stamComp)
			{
				stamComp->boostActive = false;
			}
		}
	}), this, m_controllerId);

	InputManager::GetInstance()->RegisterEventCallback(EventListener::BUTTON_START, new PressCommand([&]() {
		for (auto& component : AutoList::get<InputPauseComponent>())
		{
			component->isPaused = true;
		}
	}), this, m_controllerId);

	addObserver(m_audioMgr);
	notify(Observer::GAME_SCENE);
}

void PlayerControllerComponent::process(float dt)
{
	if (!isHooked)
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
}
