#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	_position = Vector(0, 300);
	_MAX_VEL = 2.25f;
	_rect.x = _position.x;
	_rect.y = _position.y;
	_rect.h = 100;
	_rect.w = 50;
	_gravity = 9.81;
	_stamina = 0;
	_staminaRect.x = 0;
	_staminaRect.y = 0;
	_staminaRect.w = 0;
	_staminaRect.h = 50;
}


Player::~Player()
{
}

void Player::Move(Direction pDirection, float pDeltaTime)
{
	switch (pDirection)
	{
	case Left:
		_acceleration.x = -_ACCEL_RATE * pDeltaTime;
		break;

	case Right:
		_acceleration.x = _ACCEL_RATE * pDeltaTime;
		break;

	case Up:
		InvertGravity();
		break;

	case Down:
		InvertGravity();
		break;

	case None:
		_acceleration = Vector(0, 0);
		ApplyFriction(pDeltaTime); // used to keep player speed at a constant rate
		break;


	default: break;
	}
}

void Player::ManageVelocity(float pDeltaTime)
{
	_velocity = _velocity + _acceleration;

	if (_velocity.x > _MAX_VEL)
		_velocity.x = _MAX_VEL;
	else if (_velocity.x < -_MAX_VEL)
		_velocity.x = -_MAX_VEL;

	_velocity.y = 1 * _gravity;

	_position = _position + _velocity * pDeltaTime;
}

void Player::Draw(SDL_Renderer * pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(pRenderer, &_staminaRect);
	SDL_RenderDrawRect(pRenderer, &_rect);
	SDL_SetRenderDrawColor(pRenderer, 0,0, 0, 255);
}

void Player::Update(float pDeltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	ManageVelocity(pDeltaTime);
	if (_position.x > SCREEN_WIDTH)
	{
		_position.x = 0;
	}
	if (_position.x < 0)
	{
		_position.x = SCREEN_WIDTH;
	}

	if (_position.y >= SCREEN_HEIGHT - _rect.h)
	{			  
		_position.y = SCREEN_HEIGHT - _rect.h;
	}			  
	if (_position.y <= 0)
	{			  
		_position.y = 0;
	}

	_staminaRect.w = _stamina;

	if (_stamina <= 100)
		_stamina += 0.01; // slow increase in stamina

	_rect.x = _position.x;
	_rect.y = _position.y;
}

void Player::ApplyFriction(float pDeltaTime)
{
	double scaler = 0.00001; // used since DT is in Milliseconds

	if (_velocity.x > 0)
		_velocity.x -= _FRICTION_RATE * (pDeltaTime / 1000); // need to scale DT
	else if (_velocity.x < 0)
		_velocity.x += _FRICTION_RATE * (pDeltaTime / 1000);

	if ((_velocity.x > -_MAX_VEL * scaler && _velocity.x < 0) ||
		(_velocity.x <  _MAX_VEL * scaler && _velocity.x > 0))
		_velocity.x = 0;
}

void Player::InvertGravity()
{
	_gravity = _gravity * -1; 
}

void Player::ApplyBoost()
{
	if (_stamina >= 100)
	{
		_velocity = (_velocity + _acceleration) * _BOOST_FORCE;
		_stamina = 0;
	}
}
