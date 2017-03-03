#include "stdafx.h"
#include "RenderSystem.h"
#include "Drawables.h"
#include "Dimensional.h"
#include "ResourceManager.h"
#include "Player.h"

void RenderSystem::init(Renderer * r)
{
	m_renderer = r;
}

void RenderSystem::process(float dt)
{
	m_renderer->clear(Colour(128, 128, 64));

	auto& scores = AutoList::get<ScoreComponent>();
	for (auto& component : scores)
	{
		SDL_Texture* tex = ResourceManager::getInstance()->getTextureByKey("web");
		m_renderer->drawTexture(tex, Rect(-(component->getComponent<StaticBodyComponent>()->size / 2) + component->getComponent<StaticBodyComponent>()->body->GetPosition(), component->getComponent<StaticBodyComponent>()->size));
	}
	
	{
		auto& components = AutoList::get<Box2DComponent>();
		for (auto& component : components)
		{
			bool isPlayer = false;
			int playerID;
			for (auto& player : AutoList::get<Player>())
			{
				if (component->ID == player->ID)
				{
					isPlayer = true;
					playerID = player->ID;
				}
			}

			if (!(isPlayer))
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
			else if(getComponentById<ScoreComponent>(playerID)->alive)
			{
				if (component->body->GetFixtureList()[0].GetDensity() > 0)
				{
					m_renderer->drawRect(Rect(Vector2D(component->body->GetPosition()) - component->size* 0.5, component->size), Colour(0, 0, 0));
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
	
	m_renderer->present();
}
