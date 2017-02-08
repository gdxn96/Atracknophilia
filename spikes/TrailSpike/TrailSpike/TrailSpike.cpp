// TrailSpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include "Player.h"
#include <cmath>

void Draw(SDL_Renderer* p_renderer, SDL_Rect trailRect)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(p_renderer, &trailRect);
}

SDL_Rect CalculateTrailSize(Player player, SDL_Rect trailRect, const double MAX_TRAIL_HEIGHT)
{
	Player p = player;  // Q: is it better to create on object passed in or just use the object parameter for checks?
	float speed = abs(p.GetVelocity().x);
	SDL_Rect trail = trailRect;

	if (p.GetVelocity().x < 0)
	{
		trail.x = p.GetRect().x + p.GetRect().w;
		trail.w = speed * 100;
	}
	else if (p.GetVelocity().x > 0)
	{
		trail.x = p.GetRect().x;
		trail.w = -speed * 100;
	}
	
	
	trail.y = p.GetRect().y + p.GetRect().h;
	
	if (abs(trailRect.h) < MAX_TRAIL_HEIGHT)
	{
		trail.h = -speed * 100;
	}

	return trail;
}

int main(int argc, char** argv)
{
	Player player;
	SDL_Rect trailRect{ 0, 0, 0, 0 }; // these values depend on the player

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const double ACCEL_RATE = 0.0001;
	const double FRICTION_RATE = 2;

	const double MAX_VELOCITY = 2.35;

	// constants for calculating trail size
	const double MAX_TRAIL_HEIGHT = 12;


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

		trailRect = CalculateTrailSize(player, trailRect, MAX_TRAIL_HEIGHT);

		player.Update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT, MAX_VELOCITY);

		SDL_RenderClear(renderer);

		Draw(renderer, trailRect);
		player.Draw(renderer);
		

		SDL_RenderPresent(renderer);
	} // end  game loop

	return 0;
}