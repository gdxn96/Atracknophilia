// PlayerMovementSpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include "Player.h"

Player player;
SDL_Rect _padRect { 400, 0, 100, 25 };
SDL_Rect _staminaRect{ 0, 0, 0, 50 };

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_STAMINA = 100;
const float STAMINA_INCREASE_RATE = 0.001;
const float STAMINA_DECREASE_RATE = 0.003;

const float ACCEL_RATE = 0.0001;
const float FRICTION_RATE = 2;

const float BOOST_FORCE = 2;
const float BOOST_DURATION = 2000;

const float MAX_VELOCITY = 0.35;
const float BOOSTED_MAX_VELOCITY = 0.65;

float gravity = 9.81;


void CheckCollisionWithPad()
{
	if (player.GetPlayerRect().x + player.GetPlayerRect().w >= _padRect.x && player.GetPlayerRect().x <= _padRect.x + _padRect.w 
		&& player.GetPlayerRect().y >= _padRect.y && player.GetPlayerRect().y <= _padRect.y + _padRect.h)
	{
		player.UpdateStamina(STAMINA_INCREASE_RATE, MAX_STAMINA);
	}
}

void Draw(SDL_Renderer* p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(p_renderer, &_staminaRect);
	SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(p_renderer, &_padRect);
}

void Update()
{
	_staminaRect.w = player.GetStamina();
	CheckCollisionWithPad();
}

void InvertGravity()
{
	gravity = -1 * gravity;
}

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Event e;
	window = SDL_CreateWindow("Spike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// calculate delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	bool quit = false;
	while (!quit) 
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					player.Move(player.Left, deltaTime, ACCEL_RATE, FRICTION_RATE, MAX_VELOCITY);
					break;
				case SDLK_RIGHT:
					player.Move(player.Right, deltaTime, ACCEL_RATE, FRICTION_RATE, MAX_VELOCITY);
					break;
				case SDLK_UP:
					InvertGravity();
					break;
				case SDLK_DOWN:
					InvertGravity();
					break;
				case SDLK_SPACE:
					player.ApplyBoost();
					break;
				}	// end switch
			}	// end key if statement
			else
			{
				player.Move(player.None, deltaTime, ACCEL_RATE, FRICTION_RATE, MAX_VELOCITY);  // apply friction to keep speed constant
			}
		}// end event while loop

		// calculate delta time
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());


		player.Update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT, STAMINA_DECREASE_RATE, BOOST_FORCE, BOOST_DURATION, gravity, MAX_VELOCITY, BOOSTED_MAX_VELOCITY);
		Update();

		SDL_RenderClear(renderer);

		Draw(renderer);
		player.Draw(renderer);

		SDL_RenderPresent(renderer);


	} // end  game loop

	return 0;
}

