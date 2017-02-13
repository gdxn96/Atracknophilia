#include "stdafx.h"
#include "RenderSystem.h"
#include "Drawables.h"
#include "Dimensional.h"

void RenderSystem::init(Renderer * r)
{
	m_renderer = r;
}

void RenderSystem::process(float dt)
{
	m_renderer->clear(Colour(0, 0, 0));

	if (true) //add debug flag later
	{
		auto& components = AutoList::get<Box2DComponent>();
		for (auto& component : components)
		{
			m_renderer->drawBox2DBody(component->body);
		}
	}
	
	m_renderer->present();
}
