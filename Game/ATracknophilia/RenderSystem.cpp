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
	m_renderer->clear(Colour(128, 128, 64));
	
	{
		auto& components = AutoList::get<Box2DComponent>();
		for (auto& component : components)
		{
			if (false) //add debug flag later
			{
				m_renderer->drawBox2DBody(component->body);
			}
			if (component->body->GetFixtureList()[0].GetDensity() > 0)
			{
				m_renderer->drawRect(Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size), Colour(0, 0, 0));
			}
			else
			{
				m_renderer->drawRectOutline(Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size), Colour(0, 0, 0));
			}
		}
	}
	{
		auto& components = AutoList::get<LineComponent>();
		for (auto& component : components)
		{
			m_renderer->drawLine(component->start, component->end);
		}
	}
	
	m_renderer->present();
}
