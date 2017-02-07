#include "stdafx.h"
#include "Player.h"



Player::Player() :
	m_position(Vector(0, 300)),
	m_rect({ (int)m_position.x, (int)m_position.y, 25, 25}),
	m_stamina(100),
	m_increasingVelocity(false),
	m_decreasingVelocity(false)
{

}


Player::~Player()
{
}

void Player::Move(Direction pDirection, float p_deltaTime, const float ACCEL_RATE, const float FRICTION_RATE, const float MAX_VELOCITY)
{
	switch (pDirection)
	{
	case Left:
		m_acceleration.x = -ACCEL_RATE * p_deltaTime;
		break;

	case Right:
		m_acceleration.x = ACCEL_RATE * p_deltaTime;
		break;

	case None:
		m_acceleration = Vector(0, 0);
		ApplyFriction(p_deltaTime, FRICTION_RATE, MAX_VELOCITY); // used to keep player speed at a constant rate
		break;


	default: break;
	}
}

void Player::ManageVelocity(float p_deltaTime, float p_gravity, const float MAX_VELOCITY)
{
	m_velocity = m_velocity + m_acceleration;

	if (m_velocity.x > MAX_VELOCITY)
		m_velocity.x = MAX_VELOCITY;
	else if (m_velocity.x < -MAX_VELOCITY)
		m_velocity.x = -MAX_VELOCITY;

	m_velocity.y = 1 * p_gravity;

	m_position = m_position + m_velocity * p_deltaTime;
}

void Player::Draw(SDL_Renderer * p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(p_renderer, &m_rect);
	SDL_SetRenderDrawColor(p_renderer, 0,0, 0, 255);
}

void Player::Update(float p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const float STAMINA_DECREASE_RATE, const float BOOST_FORCE, const float BOOST_DURATION, float p_gravity, const float MAX_VELOCITY, const float BOOSTED_MAX_VELOCITY)
{

	if (!m_decreasingVelocity)
		ManageVelocity(p_deltaTime, p_gravity, MAX_VELOCITY);

	if (m_position.x > SCREEN_WIDTH)
	{
		m_position.x = 0;
	}
	if (m_position.x < 0)
	{
		m_position.x = SCREEN_WIDTH;
	}

	if (m_position.y >= SCREEN_HEIGHT - m_rect.h)
	{			  
		m_position.y = SCREEN_HEIGHT - m_rect.h;
	}			  
	if (m_position.y <= 0)
	{			  
		m_position.y = 0;
	}

	if (m_increasingVelocity)
		IncreaseMaximumVelocity(p_deltaTime, STAMINA_DECREASE_RATE, BOOST_FORCE, BOOST_DURATION, BOOSTED_MAX_VELOCITY, p_gravity);

	if (m_decreasingVelocity)
		DecelerateFromBoostedVelocity(p_deltaTime, BOOST_FORCE, BOOST_DURATION, MAX_VELOCITY, p_gravity, BOOSTED_MAX_VELOCITY);


	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
}

void Player::ApplyFriction(float p_deltaTime, const float FRICTION_RATE, const float MAX_VELOCITY)
{
	double scaler = 0.00001; // used since DT is in Milliseconds (this value is the minValue - must be very close to 0)

	if (m_velocity.x > 0)
		m_velocity.x -= FRICTION_RATE * (p_deltaTime / 1000); // need to scale DT
	else if (m_velocity.x < 0)
		m_velocity.x += FRICTION_RATE * (p_deltaTime / 1000);

	if ((m_velocity.x > -MAX_VELOCITY * scaler && m_velocity.x < 0) ||
		(m_velocity.x <  MAX_VELOCITY * scaler && m_velocity.x > 0))
		m_velocity.x = 0;
}

void Player::Boost(Boosting p_boostType)
{
	switch (p_boostType)
	{
	case Increase:
		m_increasingVelocity = true;
		m_decreasingVelocity = false;
		break;
	case Decrease:
		m_increasingVelocity = false;
		m_decreasingVelocity = true;
		break;
	}
}

void Player::ApplyBoost()
{
	if (m_stamina >= 100)
	{
		m_boostTimer = 0;
		Boost(Increase);
	}
}

void Player::IncreaseMaximumVelocity(float p_deltaTime, const float STAMINA_DECREASE_RATE, const float BOOST_FORCE, const float BOOST_DURATION, const float BOOSTED_MAX_VELOCITY, float p_gravity)
{
	m_stamina -= STAMINA_DECREASE_RATE;
	m_boostTimer += p_deltaTime;
	m_velocity = (m_velocity + m_acceleration) * BOOST_FORCE;
	ManageVelocity(p_deltaTime, p_gravity, BOOSTED_MAX_VELOCITY);

	if (m_boostTimer > BOOST_DURATION) // 2 seconds of a boost
	{
		m_boostTimer = 0;
		Boost(Decrease);
	}
}

void Player::DecelerateFromBoostedVelocity(float p_deltaTime, const float BOOST_FORCE, const float BOOST_DURATION, const float MAX_VELOCITY, float p_gravity, const float BOOSTED_MAX_VELOCITY)
{
	m_boostTimer += p_deltaTime;
	if (m_boostTimer < BOOST_DURATION)
	{
		float difference = BOOSTED_MAX_VELOCITY - MAX_VELOCITY;
		float max = MAX_VELOCITY;

		// TODO: Fix this 

		ManageVelocity(p_deltaTime, p_gravity, MAX_VELOCITY);
	}
	else if (m_boostTimer > BOOST_DURATION)
	{
		ManageVelocity(p_deltaTime, p_gravity, MAX_VELOCITY);
	}
}

SDL_Rect Player::GetPlayerRect()
{
	return m_rect;
}

void Player::UpdateStamina(const float STAMINA_RATE, const float MAX_STAMINA)
{
	if (m_stamina < MAX_STAMINA)
		m_stamina += STAMINA_RATE;
}

float Player::GetStamina()
{
	return m_stamina;
}
