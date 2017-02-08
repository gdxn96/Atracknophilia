#pragma once

#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif

#include "ResourceManager.h"

class Game
{
public:
	Game();														// Constructor
	~Game();													// Standard destructor

	bool					init();								// Standard initialiser
	void					destroy();							// Function to destroy all game objects

	void					loop();								// Standard game loop

private:
	SDL_Window*				m_window;							// The window object
	SDL_Renderer*			m_renderer;							// The renderer object
	ResourceManager*		m_resourceManager;					// A manager for all assets in the game

	unsigned int			m_lastTime;							// Time of last update
	unsigned int			m_startTicks;
	bool					m_quit;								// Boolean to quit out of the game

	void					update();							// Standard update
	void					render();							// Standard render
	void					processInput();						// Gets the user input
};

