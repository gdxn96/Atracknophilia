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
	//{
	//	auto& components = AutoList::get<Box2DComponent>();
	//	for (auto& component : components)
	//	{
	//		if (component->body->GetFixtureList()[0].GetDensity() > 0)
	//		{
	//			if (!(component->size == Vector2D::ZERO))
	//			{
	//				m_renderer->drawRect(Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size), Colour(0, 0, 0));
	//			}
	//			else
	//			{
	//				m_renderer->drawFilledPoly(component->body);
	//			}
	//		}
	//	}
	//}
	{
		auto& components = AutoList::get<LineComponent>();
		for (auto& component : components)
		{
			m_renderer->drawLine(component->start, component->end);
		}
	}
	{
		auto& components = AutoList::get<AnimationComponent>();
		for (auto& component : components)
		{
			auto p = component->getParent();
			auto b = p->getComponent<Box2DComponent>();
			component->animation.drawAtPosition(m_renderer, Vector2D(b->body->GetPosition().x - b->size.width / 2, b->body->GetPosition().y - b->size.height / 2), Vector2D(b->size), 0);
		}
	}
	
	m_renderer->present();
}

void RenderSystem::setLevel(LEVELS levelKey)
{
	if (levelKey == LEVELS::LEVEL1) {
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
