// PlayerMovementSpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include "Player.h"

Player player;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
					player.Move(player.Left, deltaTime);
					break;
				case SDLK_RIGHT:
					player.Move(player.Right, deltaTime);
					break;
				case SDLK_UP:
					player.Move(player.Up, deltaTime);
					break;
				case SDLK_DOWN:
					player.Move(player.Down, deltaTime);
					break;
				case SDLK_SPACE:
					player.ApplyBoost();
					break;
				}	// end switch
			}	// end key if statement
			else
			{
				player.Move(player.None, deltaTime);  // apply friction to keep speed constant
			}
		}// end event while loop


		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		SDL_RenderClear(renderer);

		player.Update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
		player.Draw(renderer);
		// draw here

		SDL_RenderPresent(renderer);


	} // end  game loop


		

	return 0;
}

