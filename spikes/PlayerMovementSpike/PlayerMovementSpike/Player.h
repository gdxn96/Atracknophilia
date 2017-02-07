#pragma once

#include "Vector.h"
#include "SDL.h"

class Player
{
public:
	Player();
	~Player();

	enum Direction
	{
		Left,
		Right,
		Up, 
		Down,
		None
	};

	enum Boosting
	{
		Increase,
		Decrease
	};

	void Move(Direction p_direction, float p_deltaTime);
	void ManageVelocity(float p_deltaTime);
	void Draw(SDL_Renderer* p_renderer);
	void Update(float p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void ApplyFriction(float p_deltaTime);
	void InvertGravity();

	void Boost(Boosting BoostType);

	void ApplyBoost();
	void IncreaseMaximumVelocity(float p_deltaTime);
	void DecreaseMaximumVeclocity();

	void CheckCollisionWithPad();

	SDL_Rect GetPlayerRect();
	

private:
	const float _ACCEL_RATE = 0.0001;
	float _FRICTION_RATE = 2;
	Vector m_acceleration;
	Vector m_velocity;
	Vector m_position;
	float m_maxVel;
	SDL_Rect m_rect;
	float _gravity;

	// boost and stamina

	float _stamina;
	const float _BOOST_FORCE = 2;
	SDL_Rect _staminaRect;
	float _boostTimer;
	const float _STAMINA_DECREASE_RATE = 0.003;
	const float _BOOST_DURATION = 2000;

	bool _increasingVelocity;
	bool _decreasingVelocity;


	// stamina pad

	SDL_Rect _padRect;

};

