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

void Player::Move(Direction pDirection, double p_deltaTime, const double ACCEL_RATE, const double FRICTION_RATE, const double MAX_VELOCITY)
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

void Player::ManageVelocity(double p_deltaTime, double p_gravity, const double MAX_VELOCITY)
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

void Player::Update(double p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const double STAMINA_DECREASE_RATE, const double BOOST_FORCE, const double BOOST_DURATION, double p_gravity, const double MAX_VELOCITY, const double BOOSTED_MAX_VELOCITY)
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

void Player::ApplyFriction(double p_deltaTime, const double FRICTION_RATE, const double MAX_VELOCITY)
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

void Player::IncreaseMaximumVelocity(double p_deltaTime, const double STAMINA_DECREASE_RATE, const int BOOST_FORCE, const double BOOST_DURATION, const double BOOSTED_MAX_VELOCITY, double p_gravity)
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

void Player::DecelerateFromBoostedVelocity(double p_deltaTime, const int BOOST_FORCE, const double BOOST_DURATION, const double MAX_VELOCITY, double p_gravity, const double BOOSTED_MAX_VELOCITY)
{
	m_boostTimer += p_deltaTime;
	if (m_boostTimer < BOOST_DURATION)
	{
		float deceleratePercentage = m_boostTimer / BOOST_DURATION;
		float initalValue = BOOSTED_MAX_VELOCITY - MAX_VELOCITY;
		float finalValue = 0;  // lerping between the difference until there is no difference ie. 0
		float decelRate = (initalValue - finalValue) * deceleratePercentage;
		ManageVelocity(p_deltaTime, p_gravity, BOOSTED_MAX_VELOCITY - decelRate);
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

void Player::UpdateStamina(const double STAMINA_RATE, const double MAX_STAMINA)
{
	if (m_stamina < MAX_STAMINA)
		m_stamina += STAMINA_RATE;
}

float Player::GetStamina()
{
	return m_stamina;
}
