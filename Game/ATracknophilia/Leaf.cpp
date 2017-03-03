#include "stdafx.h"
#include "Leaf.h"
#include "EntityFactory.h"
#include "RaceManager.h"

UseAbility::UseAbility(/*AudioManager* audioMgr*/) {/* addObserver(audioMgr);*/ }

UseAbility::~UseAbility() {}

Node::Status UseAbility::Update(IEntity* p, float dt, bool isHooked)
{
	if (!isHooked)
	{
		auto a = p->getComponent<AbilityComponent>();
		auto c = p->getComponent<Box2DComponent>();
		if (a && c)
		{
			const auto none = a->NONE;
			const auto webDrop = a->WEB_DROP;
			const auto slowShot = a->SLOW_SHOT;
			const auto swapShot = a->SWAP_SHOT;

			switch(a->ability)
			{
			case none:
				break;
			case webDrop:
				EntityFactory::SpawnWebDrop(c->body->GetPosition().x, c->body->GetPosition().y, 1, 1);
				a->ability = a->NONE;
				return Status::Success;
			case slowShot:
				EntityFactory::SpawnSlowShot(c->body->GetPosition().x, c->body->GetPosition().y - 1, 1, 1, p->ID);
				a->ability = a->NONE;
				return Status::Success;
			case swapShot:
				auto h = p->getComponent<HookComponent>();
				if (h)
				{
					p->deleteComponent<HookComponent>();
				}
				vector<Player*> players = RaceManager::getInstance()->getPlayers();
				int targetID = 1;
				for (int i = 0; i < players.size(); i++)
				{
					if (i + 1 == players.size())
					{
					}
					else if (players[i]->ID == p->ID)
					{
						auto targetBody = players[i + 1]->getComponent<Box2DComponent>()->body;
						auto obstacle = PhysicsSystem::RayCastToStaticObject(c->body->GetPosition(), targetBody->GetPosition(), 50);
					if (!obstacle.first)
					{
						b2Vec2 dis = (c->body->GetPosition() - targetBody->GetPosition());
						p->AddComponent(new SwapComponent(p->ID, c->body->GetPosition(), targetBody->GetPosition(), c->body, players[i + 1]));
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
						else if (players[i + 1]->getComponent<PlayerControllerComponent>())
						{
							players[i + 1]->getComponent<PlayerControllerComponent>()->isHooked = true;
						}
						targetBody->SetGravityScale(0);
						c->body->SetGravityScale(0);
					}
					i = players.size();
				}
				}
				a->ability = a->NONE;
				return Status::Success;
			}
		}
	}
	return Status::Failure;
}