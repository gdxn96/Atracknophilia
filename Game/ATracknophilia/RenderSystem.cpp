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
			if (component->body->GetFixtureList()[0].GetDensity() > 0)
			{
				if (!(component->size == Vector2D::ZERO))
				{
					m_renderer->drawRect(Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size), Colour(0, 0, 0));
				}
				else
				{
					m_renderer->drawFilledPoly(component->body);
				}
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
