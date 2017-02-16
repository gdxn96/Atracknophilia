#include "stdafx.h"
#include "RenderSystem.h"
#include "Drawables.h"
#include "Dimensional.h"
#include "ResourceManager.h"

void RenderSystem::init(Renderer * r)
{
	m_renderer = r;
}

void RenderSystem::process(float dt)
{
	m_renderer->clear(Colour(0, 0, 0));
		
	auto& components = AutoList::get<Box2DComponent>();
	
	for (auto& component : components)
	{
		if (true) //add debug flag later
		{
			m_renderer->drawBox2DBody(component->body);
		}
		m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey(""), Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size));
	}

	//auto& obstacles = AutoList::get<ObstacleComponent>();
	//for (auto& obstacle : obstacles)
	//{
	//	if (true) //add debug flag later
	//	{
	//		m_renderer->drawBox2DBody(obstacle->body);
	//	}
	//	m_renderer->drawTexture(ResourceManager::getInstance()->getTextureByKey(""), Rect(Vector2D(obstacle->body->GetPosition()) - obstacle->size* 0.5, obstacle->size));
	//}
	
	m_renderer->present();
}
