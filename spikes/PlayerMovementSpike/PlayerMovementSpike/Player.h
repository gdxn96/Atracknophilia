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
		None
	};

	enum Boosting
	{
		Increase,
		Decrease
	};

	// public methods
	void Move(Direction p_direction, float p_deltaTime, const float ACCEL_RATE, const float FRICTION_RATE, const float MAX_VELOCITY);
	void Draw(SDL_Renderer* p_renderer);
	void Update(float p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const float STAMINA_DECREASE_RATE, const float BOOST_FORCE, const float BOOST_DURATION, float p_gravity, const float MAX_VELOCITY, const float BOOSTED_MAX_VELOCITY);
	void ApplyBoost();
	void UpdateStamina(const float STAMINA_RATE, const float MAX_STAMINA);

	// getters
	SDL_Rect GetPlayerRect();
	float GetStamina();

private:
	// member variables
	Vector m_acceleration;
	Vector m_velocity;
	Vector m_position;
	SDL_Rect m_rect;
	float m_stamina;

	// boost and stamina
	float m_boostTimer;
	bool m_increasingVelocity;
	bool m_decreasingVelocity;

	// private methods
	void ManageVelocity(float p_deltaTime, float p_gravity, const float MAX_VELOCITY);
	void ApplyFriction(float p_deltaTime, const float FRICTION_RATE, const float MAX_VELOCITY);
	void IncreaseMaximumVelocity(float p_deltaTime, const float STAMINA_DECREASE_RATE, const float BOOST_FORCE, const float BOOST_DURATION, const float BOOSTED_MAX_VELOCITY, float p_gravity);
	void DecelerateFromBoostedVelocity(float p_deltaTime, const float BOOST_FORCE, const float BOOST_DURATION, const float MAX_VELOCITY, float p_gravity, const float BOOSTED_MAX_VELOCITY);
	void Boost(Boosting p_boostType);
};

