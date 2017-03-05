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

	auto& scores = AutoList::get<ScoreComponent>();
	for (auto& component : scores)
	{
		SDL_Texture* tex = ResourceManager::getInstance()->getTextureByKey("placeholder");
		if (component->colourID == 0)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("bluehud");
		}
		if (component->colourID == 1)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("greenhud");
		}
		if (component->colourID == 2)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("redhud");
		}
		if (component->colourID == 3)
		{
			tex = ResourceManager::getInstance()->getTextureByKey("yellowhud");
		}

		Rect drawPos = Rect(110 * component->colourID, 3, 100, 75);

		for (int i = 0; i < component->rounds; i++)
		{
			Rect counterPos = Rect((drawPos.pos.x + 4) + 33 * i, 17, 27, 27);
			m_renderer->drawHud(ResourceManager::getInstance()->getTextureByKey("counter"), counterPos);
		}

		Rect staminaRect = Rect(drawPos.pos.x, 55, 1 * component->getParent()->getComponent<StaminaComponent>()->stamina, 15);
		//std::cout << "stamina : " << component->getParent()->getComponent<StaminaComponent>()->stamina << endl;

		m_renderer->drawHud(ResourceManager::getInstance()->getTextureByKey("stamina"), staminaRect);

		m_renderer->drawHud(tex, drawPos);
	}
	
	m_renderer->present();
}
