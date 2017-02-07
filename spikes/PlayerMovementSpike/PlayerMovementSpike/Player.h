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

	void Move(Direction pDirection, float pDeltaTime);
	void ManageVelocity(float pDeltaTime);
	void Draw(SDL_Renderer* pRenderer);
	void Update(float pDeltaTime, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void ApplyFriction(float pDeltaTime);
	void InvertGravity();

	void Boost(Boosting pBoostType, float pDeltaTime);

	void ApplyBoost(float pDeltaTime);
	void IncreaseMaximumVelocity(float pDeltaTime);
	void DecreaseMaximumVeclocity(float pDeltaTime);

private:
	const float _ACCEL_RATE = 0.0001;
	float _FRICTION_RATE = 2;
	Vector _acceleration;
	Vector _velocity;
	Vector _position;
	float _MAX_VEL;
	SDL_Rect _rect;
	float _gravity;

	// boost and stamina

	float _stamina;
	const float _BOOST_FORCE = 2;
	SDL_Rect _staminaRect;
	float _boostTimer;

	bool _increasingVelocity;
	bool _decreasingVelocity;
};

