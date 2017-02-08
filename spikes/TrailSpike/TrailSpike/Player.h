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

	// public methods
	void Move(Direction p_direction, double p_deltaTime, const double ACCEL_RATE, const double FRICTION_RATE, const double MAX_VELOCITY);
	void Draw(SDL_Renderer* p_renderer);
	void Update(double p_deltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const double MAX_VELOCITY);

	// getters
	Vector GetVelocity();
	SDL_Rect GetRect();
	
private:
	// member variables
	Vector m_acceleration;
	Vector m_velocity;
	Vector m_position;
	SDL_Rect m_rect;

	// private methods
	void ManageVelocity(double p_deltaTime, const double MAX_VELOCITY);
	void ApplyFriction(double p_deltaTime, const double FRICTION_RATE, const double MAX_VELOCITY);
};

