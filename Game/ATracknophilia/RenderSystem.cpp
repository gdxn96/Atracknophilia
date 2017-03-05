#include "stdafx.h"
#include "RenderSystem.h"
#include "Drawables.h"
#include "Dimensional.h"
#include "ResourceManager.h"
#include "Entities.h"

void RenderSystem::init(Renderer * r)
{
	m_renderer = r;
	m_levelKey = "mapone";
	m_levelRect = Rect(0, 0, 400, 395);

}

void RenderSystem::process(float dt)
{
	m_renderer->clear(Colour(128, 128, 64));
	m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey(m_levelKey), m_levelRect);

	auto& softBoxes = AutoList::get<SoftBox>();
	for (auto& component : softBoxes)
	{
		m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey("web"), Rect(-(component->getComponent<SensorComponent>()->size / 2)+component->getComponent<SensorComponent>()->body->GetPosition(), component->getComponent<SensorComponent>()->size));
	}

	auto& webDrops = AutoList::get<WebDrop>();
	for (auto& component : webDrops)
	{
		m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey("web"), Rect(-(component->getComponent<StaticBodyComponent>()->size / 2) + component->getComponent<StaticBodyComponent>()->body->GetPosition(), component->getComponent<StaticBodyComponent>()->size));
	}

	auto& boostPads = AutoList::get<BoostPad>();
	for (auto& component : boostPads)
	{
		m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey("boost"), Rect(-(component->getComponent<SensorComponent>()->size / 2) + component->getComponent<SensorComponent>()->body->GetPosition(), component->getComponent<SensorComponent>()->size));
	}

	auto& powerups = AutoList::get<PowerUp>();
	for (auto& component : powerups)
	{
		m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey("boxrandom"), Rect(-(component->getComponent<SensorComponent>()->size / 2) + component->getComponent<SensorComponent>()->body->GetPosition(), component->getComponent<SensorComponent>()->size));
	}

	auto& slowShots = AutoList::get<SlowShot>();
	for (auto& component : slowShots)
	{
		Vector2D angle = component->getComponent<SlowShotComponent>()->body->GetLinearVelocity();
		m_renderer->drawTextureWithAngle(ResourceManager::getInstance()->getTextureByKey("webattack"), Rect(-(component->getComponent<SlowShotComponent>()->size / 2) + component->getComponent<SlowShotComponent>()->body->GetPosition(), component->getComponent<SlowShotComponent>()->size), Vector2D::AngleDeg(angle, Vector2D(0,0)));
	}

	{
		auto& components = AutoList::get<LineComponent>();
		for (auto& component : components)
		{
			m_renderer->drawLine(component->start, component->end);
		}

		//auto& boxes = AutoList::get<Box2DComponent>();
		//for (auto& box : boxes)
		//{
		//	bool isPlayer = false;
		//	int playerID;
		//	for (auto& player : AutoList::get<Player>())
		//	{
		//		if (box->ID == player->ID)
		//		{
		//			isPlayer = true;
		//			playerID = player->ID;
		//		}
		//	}

		//	if (!(isPlayer))
		//	{
		//		if (box->body->GetFixtureList()[0].GetDensity() > 0)
		//		{
		//			if (!(box->size == Vector2D::ZERO))
		//			{
		//				m_renderer->drawRect(Rect(Vector2D(box->body->GetPosition()) - box->size* 0.5, box->size), Colour(0, 0, 0));
		//			}
		//			else
		//			{
		//				m_renderer->drawFilledPoly(box->body);
		//			}
		//		}
		//	}
		//	else if (getComponentById<ScoreComponent>(playerID)->alive)
		//	{
		//		if (box->body->GetFixtureList()[0].GetDensity() > 0)
		//		{
		//			m_renderer->drawRect(Rect(Vector2D(box->body->GetPosition()) - box->size* 0.5, box->size), Colour(0, 0, 0));
		//		}
		//	}
		//}
	}
	{
		auto& components = AutoList::get<AnimationComponent>();
		for (auto& component : components)
		{
			auto p = component->getParent();
			auto b = p->getComponent<Box2DComponent>();
			component->animation.drawAtPosition(m_renderer, Vector2D(b->body->GetPosition().x - b->size.width * 2, b->body->GetPosition().y - b->size.height * 2), Vector2D(b->size *4), 0);
		}
	}

	auto& scores = AutoList::get<AnimationComponent>();
	for (auto& component : scores)
	{
		SDL_Texture* tex = ResourceManager::getInstance()->getTextureByKey("placeholder");
		if (component->coulourID == 0)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("bluehud");
		}
		if (component->coulourID == 1)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("greenhud");
		}
		if (component->coulourID == 2)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("redhud");
		}
		if (component->coulourID == 3)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("yellowhud");
		}

		Rect drawPos = Rect(110 * component->coulourID, 3, 100, 75);

		for (int i = 0; i < component->getParent()->getComponent<ScoreComponent>()->rounds; i++)
		{
			Rect counterPos = Rect((drawPos.pos.x + 4) + 33 * i, 17, 27, 27);
			m_renderer->drawHud(ResourceManager::getInstance()->getTextureByKey("counter"), counterPos);
		}

		Rect staminaRect = Rect(drawPos.pos.x, 55, 1 * component->getParent()->getComponent<StaminaComponent>()->stamina, 15);
		std::cout << "stamina : " << component->getParent()->getComponent<StaminaComponent>()->stamina << endl;

		m_renderer->drawHud(ResourceManager::getInstance()->getTextureByKey("stamina"), staminaRect);

		m_renderer->drawHud(tex, drawPos);
	}
	
	m_renderer->present();
}

void RenderSystem::setLevel(LEVELS levelKey)
{
	if (levelKey == LEVELS::LEVEL1) 
	{
		m_levelKey = "mapone";
		m_levelRect = Rect(0, 0, 400, 395);
	}
	else if (levelKey == LEVELS::LEVEL2) {
		m_levelKey = "maptwo";
		m_levelRect = Rect(0, 0, 330, 164);
	}
	else if (levelKey == LEVELS::LEVEL3) {
		m_levelKey = "mapthree";
		m_levelRect = Rect(0, 0, 338, 146);
	}
	else if (levelKey == LEVELS::LEVEL4) {
		m_levelKey = "mapfour";
		m_levelRect = Rect(0, 0, 295, 150);
	}
}
