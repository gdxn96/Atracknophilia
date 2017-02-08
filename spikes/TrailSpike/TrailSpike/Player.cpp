#include "stdafx.h"
#include "Player.h"

Player::Player() :
	m_position(Vector(0, 600)),
	m_rect({ (int)m_position.x, (int)m_position.y, 25, 25})
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

void Player::ManageVelocity(double p_deltaTime, const double MAX_VELOCITY)
{
	m_velocity = m_velocity + m_acceleration;

	if (m_velocity.x > MAX_VELOCITY)
		m_velocity.x = MAX_VELOCITY;
	else if (m_velocity.x < -MAX_VELOCITY)
		m_velocity.x = -MAX_VELOCITY;

	m_position = m_position + m_velocity * p_deltaTime;
}

void Player::Draw(SDL_Renderer * p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(p_renderer, &m_rect);
	SDL_SetRenderDrawColor(p_renderer, 0,0, 0, 255);
}

void Player::Update(double p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const double MAX_VELOCITY)
{
	ManageVelocity(p_deltaTime, MAX_VELOCITY);

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

	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
}

Vector Player::GetVelocity()
{
	return m_velocity;
}

SDL_Rect Player::GetRect()
{
	return m_rect;
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