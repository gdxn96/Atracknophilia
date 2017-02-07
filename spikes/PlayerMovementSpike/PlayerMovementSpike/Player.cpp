#include "stdafx.h"
#include "Player.h"



Player::Player() :
	m_position(Vector(0, 300)),
	m_maxVel(0.35f),
	m_rect(SDL_Rect{ m_position.x, m_position.y, 25, 25}),
	_gravity(9.81),
	_stamina(100),
	_staminaRect(SDL_Rect{0, 0, 0, 50}),
	_increasingVelocity(false),
	_decreasingVelocity(false),
	_padRect(SDL_Rect{ 400, 0, 100, 25 })
{

}


Player::~Player()
{
}

void Player::Move(Direction pDirection, float p_deltaTime)
{
	switch (pDirection)
	{
	case Left:
		m_acceleration.x = -_ACCEL_RATE * p_deltaTime;
		break;

	case Right:
		m_acceleration.x = _ACCEL_RATE * p_deltaTime;
		break;

	case Up:
		InvertGravity();
		break;

	case Down:
		InvertGravity();
		break;

	case None:
		m_acceleration = Vector(0, 0);
		ApplyFriction(p_deltaTime); // used to keep player speed at a constant rate
		break;


	default: break;
	}
}

void Player::ManageVelocity(float p_deltaTime)
{
	m_velocity = m_velocity + m_acceleration;

	if (m_velocity.x > m_maxVel)
		m_velocity.x = m_maxVel;
	else if (m_velocity.x < -m_maxVel)
		m_velocity.x = -m_maxVel;

	m_velocity.y = 1 * _gravity;

	m_position = m_position + m_velocity * p_deltaTime;
}

void Player::Draw(SDL_Renderer * p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(p_renderer, &_staminaRect);
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(p_renderer, &m_rect);
	SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(p_renderer, &_padRect);
	SDL_SetRenderDrawColor(p_renderer, 0,0, 0, 255);
}

void Player::Update(float p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	ManageVelocity(p_deltaTime);
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

	_staminaRect.w = _stamina;

	CheckCollisionWithPad();


	if (_increasingVelocity)
		IncreaseMaximumVelocity(p_deltaTime);

	if (_decreasingVelocity)
		DecreaseMaximumVeclocity();


	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
}

void Player::ApplyFriction(float p_deltaTime)
{
	double scaler = 0.00001; // used since DT is in Milliseconds (this value is the minValue - must be very close to 0)

	if (m_velocity.x > 0)
		m_velocity.x -= _FRICTION_RATE * (p_deltaTime / 1000); // need to scale DT
	else if (m_velocity.x < 0)
		m_velocity.x += _FRICTION_RATE * (p_deltaTime / 1000);

	if ((m_velocity.x > -m_maxVel * scaler && m_velocity.x < 0) ||
		(m_velocity.x <  m_maxVel * scaler && m_velocity.x > 0))
		m_velocity.x = 0;
}

void Player::InvertGravity()
{
	_gravity = _gravity * -1; 
}

void Player::Boost(Boosting BoostType)
{
	switch (BoostType)
	{
	case Increase:
		_increasingVelocity = true;
		_decreasingVelocity = false;
		break;
	case Decrease:
		_increasingVelocity = false;
		_decreasingVelocity = true;
		break;
	}
}

void Player::ApplyBoost()
{
	if (_stamina >= 100)
	{
		Boost(Increase);
	}
}

void Player::IncreaseMaximumVelocity(float p_deltaTime)
{
	_stamina -= _STAMINA_DECREASE_RATE;
	_boostTimer += p_deltaTime;
	m_velocity = (m_velocity + m_acceleration) * _BOOST_FORCE;
	m_maxVel = 0.75f;

	if (_boostTimer > _BOOST_DURATION) // 2 seconds of a boost
	{
		_boostTimer = 0;
		Boost(Decrease);
	}
}

void Player::DecreaseMaximumVeclocity()
{
	m_maxVel = 0.35f;
}

void Player::CheckCollisionWithPad()
{
	if (m_rect.x + m_rect.w >= _padRect.x && m_rect.x <= _padRect.x + _padRect.w && m_rect.y >= _padRect.y && m_rect.y <= _padRect.y + _padRect.h)
	{
		if (_stamina <= 100) 
			_stamina += 0.001; 
	}
}

SDL_Rect Player::GetPlayerRect()
{
	return m_rect;
}
