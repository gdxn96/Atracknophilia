#include "stdafx.h"
#include "RenderSystem.h"
#include "Drawables.h"
#include "Dimensional.h"
#include "ResourceManager.h"
#include "Entities.h"


void RenderSystem::init(Renderer * r, LEVELS levelKey)
{
	m_renderer = r;
	if (levelKey == LEVELS::ONE){
		m_levelKey = "mapone";
		m_levelRect = Rect(0, 0, 400, 395);
	}	
	else if (levelKey == LEVELS::TWO){
		m_levelKey = "maptwo";
		m_levelRect = Rect(0, 0, 330, 164);
	}	
	else if (levelKey == LEVELS::THREE){
		m_levelKey = "mapthree";
		m_levelRect = Rect(0, 0, 338, 146);
	}	
	else if (levelKey == LEVELS::FOUR){
		m_levelKey = "mapfour";
		m_levelRect = Rect(0, 0, 295, 150);
	}
		

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
