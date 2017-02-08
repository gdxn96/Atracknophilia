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
	void Move(Direction p_direction, double p_deltaTime, const double ACCEL_RATE, const double FRICTION_RATE, const double MAX_VELOCITY);
	void Draw(SDL_Renderer* p_renderer);
	void Update(double p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const double STAMINA_DECREASE_RATE, const double BOOST_FORCE, const double BOOST_DURATION, double p_gravity, const double MAX_VELOCITY, const double BOOSTED_MAX_VELOCITY);
	void ApplyBoost();
	void UpdateStamina(const double STAMINA_RATE, const double MAX_STAMINA);

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
	void ManageVelocity(double p_deltaTime, double p_gravity, const double MAX_VELOCITY);
	void ApplyFriction(double p_deltaTime, const double FRICTION_RATE, const double MAX_VELOCITY);
	void IncreaseMaximumVelocity(double p_deltaTime, const double STAMINA_DECREASE_RATE, const int BOOST_FORCE, const double BOOST_DURATION, const double BOOSTED_MAX_VELOCITY, double p_gravity);
	void DecelerateFromBoostedVelocity(double p_deltaTime, const int BOOST_FORCE, const double BOOST_DURATION, const double MAX_VELOCITY, double p_gravity, const double BOOSTED_MAX_VELOCITY);
	void Boost(Boosting p_boostType);
};

