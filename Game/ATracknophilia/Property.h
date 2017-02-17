#pragma once
#include "ECSInterfaces.h"

struct StaminaComponent : public IComponent, public AutoLister<StaminaComponent>
{
	StaminaComponent(int id, float stamina)
		: IComponent(id)
		, m_stamina(stamina)
	{}

	float m_stamina;
};

struct MaxAccelerationComponent : public IComponent, public AutoLister<MaxAccelerationComponent>
{
	MaxAccelerationComponent(int id, float acceleration)
		: IComponent(id)
		, m_maxAcceleration(acceleration)
	{}

	float m_maxAcceleration;
};

struct MaxVelocityComponent : public IComponent, public AutoLister<MaxVelocityComponent>
{
	MaxVelocityComponent(int id, float velocity)
		: IComponent(id)
		, m_maxVelocity(velocity)
	{}

	float m_maxVelocity;
};

struct BoostComponent : public IComponent, public AutoLister<BoostComponent>
{
	BoostComponent(int id)
		: IComponent(id)
		, MAX_VELOCITY(50)
		, BOOSTED_MAX_VELOCITY(80)
		, BOOSTED_ACCELERATION(150)
		, m_boostTime(0)
		, m_decelerateTime(0)
		, m_boostActive(false)
	{}

	const float MAX_VELOCITY;
	const float BOOSTED_MAX_VELOCITY;
	const float BOOSTED_ACCELERATION;
	float m_boostTime;
	float m_decelerateTime;
	bool m_boostActive;
};