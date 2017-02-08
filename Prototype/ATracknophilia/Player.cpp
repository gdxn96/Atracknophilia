#include "stdafx.h"
#include "Player.h"

Player::Player() 
	:	m_box(7, 5, 1, 1, false)
{
}

void Player::Render(SDL_Renderer * r)
{
	m_box.Render(r);
}

void Player::update(float dt)
{
	m_box.update(dt);
}

void Player::ApplyForce(Vector v)
{
	m_box.m_body->ApplyLinearImpulseToCenter(b2Vec2(v.x, v.y), true);
}
