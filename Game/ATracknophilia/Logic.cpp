#include "stdafx.h"
#include "Logic.h"
#include "Player.h"

void BoostPadResponseComponent::beginContact(IEntity * e)
{
	if (e)
	{
		auto players = AutoList::get<Player>();
		for (auto player : players)
		{
			if (e->ID == player->ID)
			{
				e->getComponent<StaminaComponent>()->m_stamina += 20;
				std::cout << "Stamina: " + std::to_string(e->getComponent<StaminaComponent>()->m_stamina) << std::endl;
				break;
			}
		}
	}
}
